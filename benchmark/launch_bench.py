import os
import stat

from subprocess import call

executable = stat.S_IEXEC | stat.S_IXGRP | stat.S_IXOTH

for filename in os.listdir('.'):
    if os.path.isfile(filename):
        st = os.stat(filename)
        mode = st.st_mode
        if mode & executable:
            # print(filename,oct(mode))
            print("executing " + filename)

            f = open("result_" + filename + ".txt", "w")
			# subprocess.call(["/home/myuser/run.sh", "/tmp/ad_xml",  "/tmp/video_xml"], stdout=f)
            call([filename,], stdout=f)
