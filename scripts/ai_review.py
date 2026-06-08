import os
import subprocess
import requests
from google import genai

REVIEW_POLICY_PATH = "review_rules/review_policy.md"


def run_command(command: list[str]) -> str:
    result = subprocess.run(
        command,
        check=True,
        text=True,
        capture_output=True,
    )
    return result.stdout


def load_text(path: str) -> str:
    with open(path, "r", encoding="utf-8") as file:
        return file.read()


def create_prompt(review_rules: str, diff_text: str) -> str:
    return f"""
以下のレビュー条件と出力形式に従って、Pull Request の差分をレビューしてください。
授業用の教材として使うため、指摘は具体的に、初心者にも理由が分かるように書いてください。

# レビュー条件
{review_rules}

# 出力形式
## Summary
変更内容の要約

## Critical
致命的な問題。なければ「なし」

## Major
修正した方がよい問題。なければ「なし」

## Minor
軽微な改善。なければ「なし」

## Good Points
良い点

## Questions
質問

# Pull Request Diff
```diff
{diff_text}
```
"""


def get_pull_request_diff() -> str:
    base_sha = os.environ["BASE_SHA"]
    head_sha = os.environ["HEAD_SHA"]
    return run_command(["git", "diff", f"{base_sha}...{head_sha}"])


def create_review_comment(prompt: str) -> str:
    client = genai.Client(api_key=os.environ["GEMINI_API_KEY"])
    response = client.models.generate_content(
        model="gemini-2.5-flash",
        contents=prompt,
    )
    text = response.text
    if not text or not text.strip():
        raise ValueError("Gemini response text is empty.")

    print(f"Generated review comment length: {len(text)}")
    return text


def post_comment(comment: str) -> None:
    if not comment or not comment.strip():
        raise ValueError("AI review comment is empty.")

    repository = os.environ["GITHUB_REPOSITORY"]
    pr_number = os.environ["PR_NUMBER"]
    github_token = os.environ["GITHUB_TOKEN"]

    url = f"https://api.github.com/repos/{repository}/issues/{pr_number}/comments"
    headers = {
        "Authorization": f"Bearer {github_token}",
        "Accept": "application/vnd.github+json",
    }
    response = requests.post(
        url,
        headers=headers,
        json={"body": comment},
        timeout=30,
    )

    print(f"POST {url}")
    print(f"GitHub API status: {response.status_code}")

    if response.status_code >= 400:
        print(response.text)

    response.raise_for_status()


def main() -> None:
    diff_text = get_pull_request_diff()
    print(f"Diff length: {len(diff_text)}")
    review_rules = load_text(REVIEW_POLICY_PATH)
    print(f"Review policy length: {len(review_rules)}")
    prompt = create_prompt(review_rules, diff_text)
    print(f"Prompt length: {len(prompt)}")
    comment = create_review_comment(prompt)
    post_comment(comment)


if __name__ == "__main__":
    main()