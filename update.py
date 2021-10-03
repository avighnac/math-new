import os
import shutil
import zipfile

# Download the file from `url` and save it locally under `file_name`:
url = "https://codeload.github.com/avighnac/math_new/zip/refs/heads/main"

if not os.path.exists("math_new.zip"):
    import urllib.request
    urllib.request.urlretrieve(url, "math_new.zip")

file_name = zipfile.ZipFile("math_new.zip")

if os.path.exists("code"):
    shutil.rmtree("code")

# Extract code from the archive
for file in file_name.namelist():
    if file.startswith('code/'):
        file_name.extract(file)

# Remove the zip file
os.remove("math_new.zip")
