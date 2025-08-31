import requests
import pandas as pd
from datetime import datetime

API_TOKEN = "4a75ee51f52de9bbdfda6af722d39023d5311741"
url = "https://api.todoist.com/rest/v2/tasks"
headers = {"Authorization": f"Bearer {API_TOKEN}"}

df = pd.read_csv("todoist_tasks.csv")

for _, row in df.iterrows():
    task = {
        "content": row["Content"],
        "description": row["Description"] if pd.notna(row["Description"]) else "",
        "priority": int(row["Priority"]) if pd.notna(row["Priority"]) else 1,
    }

    if pd.notna(row["Due"]):
        due_time = datetime.strptime(row["Due"], "%Y-%m-%d %H:%M")
        task["due_datetime"] = due_time.strftime("%Y-%m-%dT%H:%M:00+08:00")

    response = requests.post(url, json=task, headers=headers)
    if response.status_code == 200:
        print(f"已建立：{task['content']}")
    else:
        print(f"失敗：{task['content']} | {response.text}")
