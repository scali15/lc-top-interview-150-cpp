#!/usr/bin/env python3
import requests
import sys
import re
import html
import os
import json
from html.parser import HTMLParser

GRAPHQL_URL = "https://leetcode.com/graphql"

QUERY = """
query questionContent($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    title
    content
    difficulty
    codeDefinition
  }
}
"""

def extract_cpp_signature(question_data):

    raw = question_data.get("codeDefinition", "")

    try:
        code_defs = json.loads(raw)
    except Exception:
        return "Error loading JSON for cpp signature"

    for entry in code_defs:
        if isinstance(entry, dict) and entry.get("text", "").lower() in ("c++", "cpp"):
            return entry.get("defaultCode", "")

    return ""


# Simple HTML → Markdown converter (best effort)
class HTML2Markdown(HTMLParser):
    def __init__(self):
        super().__init__()
        self.out = []
        self.in_li = False

    def handle_starttag(self, tag, attrs):
        if tag == "strong":
            self.out.append("**")
        elif tag == "em":
            self.out.append("_")
        elif tag == "code":
            self.out.append("`")
        elif tag == "li":
            self.in_li = True
            self.out.append("- ")
        elif tag == "p":
            self.out.append("\n")
        elif tag == "sup":
            self.out.append("^")

    def handle_endtag(self, tag):
        if tag == "strong":
            self.out.append("**")
        elif tag == "em":
            self.out.append("_")
        elif tag == "code":
            self.out.append("`")
        elif tag == "li":
            self.in_li = False
            self.out.append("\n")
        elif tag == "sup":
            pass 

    def handle_data(self, data):
        self.out.append(html.unescape(data))

    def get_md(self):
        raw = "".join(self.out)
        raw = raw.replace("\u00A0", " ")
        raw = re.sub(r"\n{3,}", "\n\n", raw)

        # Add double-space MD line breaks for Input/Output/Explanation lines
        for label in ("Input", "Output", "Explanation"):
            raw = re.sub(
                rf"^(\*\*{label}:.*)$",
                r"\1  ",
                raw,
                flags=re.MULTILINE,
            )

        return raw.strip() + "\n"



def fetch_markdown(slug: str, cookie: str):
    headers = {
        "Content-Type": "application/json",
        "Cookie": f"LEETCODE_SESSION={cookie}",
        "Referer": f"https://leetcode.com/problems/{slug}/",
        "User-Agent": "Mozilla/5.0",
    }

    payload = {
        "query": QUERY,
        "variables": {"titleSlug": slug},
        "operationName": "questionContent"
    }

    r = requests.post(GRAPHQL_URL, headers=headers, json=payload)

    # Handle HTTP-level errors
    if r.status_code != 200:
        print("HTTP error:", r.status_code)
        print(r.text[:500])
        sys.exit(2)

    # Try decoding JSON
    try:
        response_json = r.json()
    except Exception:
        print("Failed to parse JSON (likely HTML returned by LeetCode):")
        print(r.text[:500])
        sys.exit(2)

    # GraphQL-level errors
    if "errors" in response_json:
        print("GraphQL errors:", response_json["errors"])
        sys.exit(2)

    data = response_json["data"]["question"]

    html_content = data["content"]
    parser = HTML2Markdown()
    parser.feed(html_content)
    description_md = parser.get_md()

    cpp_sig = extract_cpp_signature(data)

    return description_md, cpp_sig


def main():
    if len(sys.argv) != 2:
        print("Usage: fetch_lc.py <slug>")
        print("Example: ./fetch_lc.py jump-game")
        sys.exit(1)

    slug = sys.argv[1]

    cookie = os.environ.get("LEETCODE_SESSION")
    if not cookie:
        print("Error: LEETCODE_SESSION was not found in environment variables.")
        print("Add this to your ~/.bashrc or ~/.zshrc:\n")
        print('    export LEETCODE_SESSION="your_cookie_here"')
        sys.exit(1)

    md, cpp_sig = fetch_markdown(slug, cookie)
    print(md)
    print("<SIG_SPLIT>")
    print(cpp_sig)

if __name__ == "__main__":
    main()
