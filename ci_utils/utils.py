import importlib
import os
import re
import subprocess

DEFAULT_ORGANIZATION_NAME = 'tao-cpp'
DEFAULT_LOGIN_USERNAME = 'fpelliccioni'
DEFAULT_USERNAME = 'tao'
DEFAULT_REPOSITORY = 'tao'

def branch_to_channel(branch):
    if branch is None:
        return "stable" #"staging"
    if branch == 'dev':
        return "testing"
    if branch.startswith('release'):
        return "stable" #"staging"
    if branch.startswith('hotfix'):
        return "stable" #"staging"
    if branch.startswith('feature'):
        return branch

    return "stable" #"staging"

def get_git_branch(default=None):
    try:
        res = subprocess.Popen(["git", "rev-parse", "--abbrev-ref", "HEAD"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output, _ = res.communicate()
        if output:
            if res.returncode == 0:
                ret = output.decode("utf-8").replace('\n', '').replace('\r', '')
                return ret
        return default
    except OSError: # as e:
        return default
    except:
        return default

def get_branch(default=None):
    branch = os.getenv("TAO_BRANCH", None)

    if branch is None: 
        branch = os.getenv("TRAVIS_BRANCH", None)

    # print("branch: %s" % (branch,))

    if branch is None: 
        branch = get_git_branch()

    # print("branch: %s" % (branch,))

    return default

def get_channel_from_branch():
    return branch_to_channel(get_branch())

def access_file(file_path):
    with open(file_path, 'r') as f:
        return f.read().replace('\n', '').replace('\r', '')

def get_content_with_dir(dir, file_name):
    file_path = os.path.join(dir, file_name)
    return access_file(file_path)

def get_content_default_with_dir(dir, file_name, default=None):
    try:
        return get_content_with_dir(dir, file_name)
    except IOError as e:
        return default

def get_channel_from_file(recipe_dir):
    return get_content_default_with_dir(recipe_dir, 'conan_channel')

def get_channel(recipe_dir):
    channel = get_channel_from_file(recipe_dir)

    if channel is None:
        channel = os.getenv("TAO_CONAN_CHANNEL", None)

    if channel is None:
        channel = get_channel_from_branch()

    if channel is None:
        channel = "stable" #"staging"

    return channel

def get_user(recipe_dir):
    return get_content_default_with_dir(recipe_dir, 'conan_user', DEFAULT_USERNAME)


def get_version_from_file(recipe_dir):
    return get_content_default_with_dir(recipe_dir, 'conan_version')

def get_version_from_branch_name():
    branch = get_branch()
    # print("get_version_from_branch_name - branch: %s" % (branch,))
    if branch is None: 
        return None
    if branch.startswith("release-") or branch.startswith("hotfix-"):
        return branch.split('-', 1)[1]
    if branch.startswith("release_") or branch.startswith("hotfix_"):
        return branch.split('_', 1)[1]
    return None

def is_development_branch():
    branch = get_branch()
    if branch is None: 
        return False

    # return branch == 'dev' or branch.startswith('feature')    

    if branch == 'master':
        return False
    if branch.startswith('release'):
        return False
    if branch.startswith('hotfix'):
        return False

    return True


def get_git_describe(default=None):
    try:
        res = subprocess.Popen(["git", "describe", "master"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output, _ = res.communicate()
        if output:
            if res.returncode == 0:
                return output.decode("utf-8").replace('\n', '').replace('\r', '')
                # return output.replace('\n', '').replace('\r', '')
        return default
    except OSError: # as e:
        return default
    except:
        return default

def get_git_branches(default=None):
    try:
        res = subprocess.Popen(["git", "ls-remote", "--heads", "origin"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output, _ = res.communicate()
        if output:
            if res.returncode == 0:
                # return output.decode("utf-8").replace('\n', '').replace('\r', '')
                return output.decode("utf-8")
        return default
    except OSError: # as e:
        return default
    except:
        return default


def release_branch_version_to_int(version):
    verarr = version.split('.')
    if len(verarr) != 3:
        return None
    verstr = verarr[0].zfill(5) + verarr[1].zfill(5) + verarr[2].zfill(5)
    return int(verstr)

def release_branch_version(branch):
    version = branch.split('-')[-1]
    return (release_branch_version_to_int(version), version)

def max_release_branch(default=None):
    branches = get_git_branches()
    # print(branches)
    if branches is None:
        return False

    max = None
    max_str = None

    for line in branches.splitlines():
        line = line.strip()
        # print(line)
        # if line.startswith("origin/release-"):
        if "release-" in line: 
            veri, vers = release_branch_version(line)
            if veri is not None:
                if max is None or veri > max:
                    max = veri
                    max_str = vers

    return (max, max_str)

def get_version_from_git_describe(default=None, is_dev_branch=False):
    describe = get_git_describe()
    describe = "v0.0.1-167-g3f9eb8d"
    
    # print('describe')
    # print(describe)

    # if describe is None:
    #     return None

    if describe is None:
        describe = "v0.0.0-"

    version = describe.split('-')[0][1:]

    if is_dev_branch:
        # print(version)
        # print(release_branch_version_to_int(version))
        
        # print(max_release_branch())

        max_release_i, max_release_s = max_release_branch()
        
        if max_release_i is not None and max_release_i > release_branch_version_to_int(version):
            version = max_release_s

        version_arr = version.split('.')
        if len(version_arr) != 3:
            # print('version has to be of the following format: xx.xx.xx')
            return None
        # version = "%s.%s.%s" % (version_arr[0], str(int(version_arr[1]) + 1), version_arr[2])
        version = "%s.%s.%s" % (version_arr[0], str(int(version_arr[1]) + 1), 0)

    return version

# def get_version(recipe_dir):
#     # print("get_version()----------------------------------------------------------")
#     # print("TAO_BRANCH:        %s" % (os.getenv("TAO_BRANCH", None),))
#     # print("TAO_CONAN_CHANNEL: %s" % (os.getenv("TAO_CONAN_CHANNEL", None),))
#     # print("TAO_FULL_BUILD:    %s" % (os.getenv("TAO_FULL_BUILD", None),))
#     # print("TAO_CONAN_VERSION: %s" % (os.getenv("TAO_CONAN_VERSION", None),))

#     # version = get_version_from_file(recipe_dir)

#     # print('------------------------------------------------------')
#     # print("version 1: %s" % (version,))

#     # if version is None:
#     #     version = os.getenv("TAO_CONAN_VERSION", None)

#     # print("version 2: %s" % (version,))
#     # print("TAO_CONAN_VERSION: %s" % (os.getenv("TAO_CONAN_VERSION", None),))

#     # if version is None:
#     #     version = get_version_from_branch_name()

#     # print("version 3: %s" % (version,))

#     # if version is None:
#     #     version = get_version_from_git_describe(None, is_development_branch())

#     # print("version 4: %s" % (version,))
#     # print('------------------------------------------------------')

#     return version

def get_conan_vars(recipe_dir):
    org_name = os.getenv("CONAN_ORGANIZATION_NAME", DEFAULT_ORGANIZATION_NAME)
    login_username = os.getenv("CONAN_LOGIN_USERNAME", DEFAULT_LOGIN_USERNAME)
    username = os.getenv("CONAN_USERNAME", get_user(recipe_dir))
    channel = os.getenv("CONAN_CHANNEL", get_channel(recipe_dir))
    version = get_version()
    return org_name, login_username, username, channel, version


def get_value_from_recipe(recipe_dir, search_string, recipe_name="conanfile.py"):
    # recipe_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', recipe_name)
    recipe_path = os.path.join(recipe_dir, recipe_name)
    with open(recipe_path, "r") as conanfile:
        contents = conanfile.read()
        result = re.search(search_string, contents)
    return result

def get_name_from_recipe(recipe_dir):
    return get_value_from_recipe(recipe_dir, r'''name\s*=\s*["'](\S*)["']''').groups()[0]

def get_archs():
    return ["x86_64"]

def get_user_repository(org_name, repository_name):
    # https://api.bintray.com/conan/tao-cpp/tao
    return "https://api.bintray.com/conan/{0}/{1}".format(org_name.lower(), repository_name)

def get_conan_upload(org_name):
    # if is_pull_request(): return ''
    repository_name = get_repository()
    return os.getenv("CONAN_UPLOAD", get_user_repository(org_name, repository_name))

def get_repository():
    return os.getenv("TAO_BINTRAY_REPOSITORY", DEFAULT_REPOSITORY)

def get_conan_upload_for_remote(org_name):
    repository_name = get_repository()
    return get_user_repository(org_name, repository_name)

def get_conan_remotes(org_name):
    remotes = [get_conan_upload_for_remote(org_name)]
    return remotes

def get_git_commit_count_per_branch(branch='master', default=0):
    try:
        res = subprocess.Popen(["git", "rev-list", "--count", branch], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output, _ = res.communicate()
        if output:
            if res.returncode == 0:
                # return output.decode("utf-8").replace('\n', '').replace('\r', '')
                return output.decode("utf-8")
        return default
    except OSError: # as e:
        return default
    except:
        return default

def get_version():
    branch = get_branch('master')
    major = os.getenv("TAO_VERSION_MAJOR", "0")
    minor = os.getenv("TAO_VERSION_MINOR", "1")
    patch = get_git_commit_count_per_branch(branch, "1")
    return "%s.%s.%s" % (major, minor, patch)

def get_conan_packager():
    pkg = importlib.import_module('conan.packager')
    return pkg

def get_builder(recipe_dir, args=None):
    name = get_name_from_recipe(recipe_dir)
    org_name, login_username, username, channel, version = get_conan_vars(recipe_dir)
    reference = "{0}/{1}".format(name, version)
    upload = get_conan_upload(org_name)
    remotes = os.getenv("CONAN_REMOTES", get_conan_remotes(org_name))

    print(org_name)
    print(remotes)
    print(upload)

    archs = get_archs()

    builder = get_conan_packager().ConanMultiPackager(
        username=username,
        login_username=login_username,
        channel=channel,
        reference=reference,
        upload=upload,
        remotes=remotes,
        archs=archs,
        )

    return builder, name
