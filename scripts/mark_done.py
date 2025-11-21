#!/usr/bin/env python3
import os
import sys
import datetime
import re

PROGRESS_FILE = "Progress.md"
TOTAL_PROBLEMS = 150

BAR_START = "<!-- PROGRESS_BAR_START -->"
BAR_END   = "<!-- PROGRESS_BAR_END -->"

CHECKLIST_BLOCK_RE = r"<!-- CHECKLIST_START:(.*?) -->(.*?)<!-- CHECKLIST_END:\1 -->"


# -----------------------------------------------------------
# Update .status file
# -----------------------------------------------------------

def update_status_file(folder):
    status_path = os.path.join(folder, ".status")

    if not os.path.exists(status_path):
        print(f"Error: no .status file found in {folder}")
        sys.exit(1)

    today = datetime.date.today().isoformat()

    with open(status_path, "r") as f:
        lines = f.readlines()

    new_lines = []
    for line in lines:
        if line.startswith("done:"):
            new_lines.append("done: true\n")
        elif line.startswith("completed:"):
            new_lines.append(f"completed: {today}\n")
        else:
            new_lines.append(line)

    with open(status_path, "w") as f:
        f.writelines(new_lines)

    return status_path


# -----------------------------------------------------------
# Find all solved problems
# -----------------------------------------------------------

def find_all_status_files():
    status_files = []
    for root, dirs, files in os.walk("problems"):
        if ".status" in files:
            status_files.append(os.path.join(root, ".status"))
    return status_files


def extract_problem_name(status_path):
    return os.path.basename(os.path.dirname(status_path))


# -----------------------------------------------------------
# Progress bar
# -----------------------------------------------------------

def generate_progress_bar(done, total):
    percent = int(done * 100 / total)
    bar_len = 50
    filled = int(bar_len * percent / 100)
    bar = "█" * filled + "░" * (bar_len - filled)
    return percent, bar


# -----------------------------------------------------------
# Update Progress.md
# -----------------------------------------------------------

def update_progress_md(solved_set):
    with open(PROGRESS_FILE, "r") as f:
        content = f.read()

    # ---- Progress bar ----
    done = len(solved_set)
    percent, bar = generate_progress_bar(done, TOTAL_PROBLEMS)

    bar_section = (
        f"{BAR_START}\n"
        f"Progress: {percent}% ({done}/{TOTAL_PROBLEMS})\n"
        f"{bar}\n"
        f"{BAR_END}"
    )

    content = re.sub(
        f"{BAR_START}.*?{BAR_END}",
        bar_section,
        content,
        flags=re.DOTALL
    )

    # ---- Checklist ----
    def rewrite_block(match):
        category = match.group(1)
        original_block = match.group(2)

        lines = original_block.strip().split("\n")
        out = []

        for line in lines:
            m = re.match(r"- \[(.)\] (.*)", line.strip())
            if not m:
                continue

            name = m.group(2)
            checked = "[x]" if name in solved_set else "[ ]"
            out.append(f"- {checked} {name}")

        return (
            f"<!-- CHECKLIST_START:{category} -->\n" +
            "\n".join(out) +
            f"\n<!-- CHECKLIST_END:{category} -->"
        )

    content = re.sub(CHECKLIST_BLOCK_RE, rewrite_block, content, flags=re.DOTALL)

    with open(PROGRESS_FILE, "w") as f:
        f.write(content)


def get_solved_problems():
    solved = set()
    for status_path in find_all_status_files():
        with open(status_path, "r") as f:
            content = f.read()
            # Check if done: true exists in the file
            if re.search(r"done:\s*true", content):
                solved.add(extract_problem_name(status_path))
    return solved




# -----------------------------------------------------------
# Main
# -----------------------------------------------------------

def main():
    if len(sys.argv) != 2:
        print("Usage: mark_done.py <problem_folder>")
        sys.exit(1)

    folder = sys.argv[1]

    if not os.path.isdir(folder):
        print(f"Error: {folder} is not a folder")
        sys.exit(1)

    # Update .status properly
    update_status_file(folder)

    # Rescan repo for solved problems
    solved = get_solved_problems()

    # Update Progress.md
    update_progress_md(solved)

    print(f"✓ Marked as done: {folder}")
    print(f"✓ Progress.md updated successfully")


if __name__ == "__main__":
    main()
