import os
import shutil
import requests
import zipfile

url = "https://raw.githubusercontent.com/avighnac/math_new/main/code.zip"

# Download the file from `url` and save it locally under `file_name`:
r = requests.get(url)

with open("code.zip", "wb") as code:
    code.write(r.content)

# Delete the directory if it exists
if os.path.exists("code"):
    shutil.rmtree("code")

# Extract the zip file
with zipfile.ZipFile("code.zip", 'r') as zip_ref:
    zip_ref.extractall(".")

# Delete the zip file
os.remove("code.zip")