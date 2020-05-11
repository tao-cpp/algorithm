import os
import pipes
import platform
from utils import get_version

if 'TRAVIS_BRANCH' in os.environ:
    branch = os.environ.get('TRAVIS_BRANCH')
elif 'APPVEYOR_REPO_BRANCH' in os.environ:
    branch = os.environ.get('APPVEYOR_REPO_BRANCH')

os.environ['TAO_BRANCH'] = branch       # needed by get_version()

#Note: duplicated in utils.branch_to_channel
if branch == 'dev':
    channel = "testing"
    full_build = "0"
else:
    channel = "stable"
    full_build = "1"

# export TAO_CONAN_VERSION="$(python ci_utils/print_version.py)"
version = get_version()

if not os.path.exists('conan_version'):
    with open("conan_version", "w") as file:
        file.write(version)

if platform.system() == "Windows":
    export_str = '$Env:TAO_BRANCH="%s"; $Env:TAO_CONAN_CHANNEL="%s"; $Env:TAO_FULL_BUILD="%s"; $Env:TAO_CONAN_VERSION="%s"; $Env:CONAN_CHANNEL="%s";'
else:
    export_str = "export TAO_BRANCH=%s TAO_CONAN_CHANNEL=%s TAO_FULL_BUILD=%s TAO_CONAN_VERSION=%s CONAN_CHANNEL=%s "

print(export_str % (pipes.quote(str(branch)), 
                    pipes.quote(str(channel)),
                    pipes.quote(str(full_build)),
                    pipes.quote(str(version)),
                    pipes.quote(str(channel)),
     ))



