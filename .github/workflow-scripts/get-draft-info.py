import json
import os
import zipfile

# Open the packaged geode mod file
archive = zipfile.ZipFile('coopeeo.customname.geode', 'r')

# Read and process the changelog
with archive.open('changelog.md') as eee:
    eeee = [line.decode('utf-8') for line in eee]

eeeeee = ''.join(eeee)
parts = eeeeee.split('##')
if len(parts) > 1:
    first_heading = parts[1].split('\r')[0].split('\n')[0]
    one = ('## ' + parts[1]).replace(first_heading, 'What\'s New This Update').replace('\n', "")
else:
    one = "What's New This Update"

# Read version from mod.json
mod_data = json.loads(archive.read('mod.json').decode('utf-8'))
two = mod_data["version"].replace("v", "")

# Write outputs for GitHub Actions
github_output = os.getenv('GITHUB_OUTPUT')
if github_output:
    with open(github_output, 'a') as file:
        file.write(f'cl={one}\n')
        file.write(f'version={two}\n')
