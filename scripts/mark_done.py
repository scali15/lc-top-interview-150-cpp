#!/usr/bin/env python3
import os
import sys
from datetime import datetime, date
import re

PROGRESS_FILE = "Progress.md"
TOTAL_PROBLEMS = 150

BAR_START = "<!-- PROGRESS_BAR_START -->"
BAR_END   = "<!-- PROGRESS_BAR_END -->"
CHECKLIST_START = "<!-- CHECKLIST_START:"
CHECKLIST_END   = "<!-- CHECKLIST_END:"


# -----------------------------------------------------------
# Mark .status as done
# -----------------------------------------------------------
def mark_status_done(folder):
    status_path = os.path.join(folder, ".status")
    if not os.path.exists(status_path):
        sys.exit(f"Error: no .status file found in {folder}")

    today = date.today().isoformat()

    with open(status_path) as f:
        lines = f.readlines()

    with open(status_path, "w") as f:
        found_completed = False

        for line in lines:
            if line.startswith("done:"):
                f.write("done: true\n")
            elif line.startswith("completed:"):
                f.write(f"completed: {today}, at: {datetime.now().strftime('%I:%M:%S %p')}\n")
                found_completed = True
            else:
                f.write(line)

        # If no completed line existed, append one
        if not found_completed:
            f.write(f"completed: {today} at {datetime.now().strftime('%I:%M:%S %p')}\n")


# -----------------------------------------------------------
# Collect solved problems
# -----------------------------------------------------------
def solved_problems():
    solved = []
    for root, dirs, files in os.walk("problems"):
        if ".status" in files:
            path = os.path.join(root, ".status")
            with open(path) as f:
                if "done: true" in f.read():
                    solved.append(os.path.basename(root))
    return set(solved)


# -----------------------------------------------------------
# Update the progress bar text
# -----------------------------------------------------------
def apply_progress_bar(content, solved_count):
    percent = solved_count * 100 // TOTAL_PROBLEMS
    bar_len = 50
    filled = bar_len * percent // 100
    bar = "█" * filled + "░" * (bar_len - filled)

    replacement = (
        f"{BAR_START}\n"
        f"Progress: {percent}% ({solved_count}/{TOTAL_PROBLEMS})\n"
        f"{bar}\n"
        f"{BAR_END}"
    )

    return re.sub(
        f"{BAR_START}.*?{BAR_END}",
        replacement,
        content,
        flags=re.DOTALL
    )

# -----------------------------------------------------------
# Rewrite checklists based on solved set
# -----------------------------------------------------------
def apply_checklists(content, solved):
    def repl(match):
        category = match.group(1)
        block = match.group(2).strip().split("\n")

        out = []
        for line in block:
            m = re.match(r"- \[(.)\] (.*)", line)
            if not m:
                continue
            name = m.group(2)
            check = "x" if name in solved else " "
            out.append(f"- [{check}] {name}")

        return (
            f"{CHECKLIST_START}{category} -->\n" +
            "\n".join(out) +
            f"\n{CHECKLIST_END}{category} -->"
        )

    pattern = rf"{CHECKLIST_START}(.*?) -->(.*?){CHECKLIST_END}\1 -->"
    return re.sub(pattern, repl, content, flags=re.DOTALL)


# -----------------------------------------------------------
# Write updated Progress.md
# -----------------------------------------------------------
def update_progress_md(solved):
    with open(PROGRESS_FILE) as f:
        content = f.read()

    content = apply_progress_bar(content, len(solved))
    content = apply_checklists(content, solved)

    with open(PROGRESS_FILE, "w") as f:
        f.write(content)


# -----------------------------------------------------------
# Main
# -----------------------------------------------------------
def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: mark_done.py <problem_folder>")

    folder = sys.argv[1]
    if not os.path.isdir(folder):
        sys.exit(f"Error: {folder} is not a folder")

    mark_status_done(folder)
    solved = solved_problems()
    update_progress_md(solved)

    print(f"✓ Marked as done: {folder}")
    print("✓ Progress.md updated")


if __name__ == "__main__":
    main()
