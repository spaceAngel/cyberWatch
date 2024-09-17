from datetime import datetime
import os
import shutil

def trailingZero(value):
	if (value  < 10):
		return "0{0}".format(value)
	else:
		return value

dt = datetime.now()

stream = os.popen('git rev-parse --short HEAD')
commit = stream.read()
stream.close()

f = open("src/Environment/compilationdata.h", "w")
data = str(int(datetime.timestamp(dt)));

f.write(
	"#pragma once \n"
	+ "#define COMPILATION_COMMIT \"" + commit.strip() + "\" \n"
	+ "#define COMPILATION_TIMESTAMP " +  data + " \n"
	+ "#define COMPILATION_TIME \"{0}-{1}-{2} {3}:{4}:{5}\" \n".format(
		dt.year,
		dt.month,
		dt.day,
		trailingZero(dt.hour),
		trailingZero(dt.minute),
		trailingZero(dt.second)
	)

)
f.close()

if os.path.isfile("NTPconf.h"):
	shutil.copy2('NTPconf.h', 'src/NTPconf.h')
else:
	if os.path.isfile("src/NTPconf.h"):
		os.remove("src/NTPconf.h")
