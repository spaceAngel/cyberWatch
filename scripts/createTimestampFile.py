from datetime import datetime

def trailingZero(value):
	if (value  < 10):
		return "0{0}".format(value)
	else:
		return value

dt = datetime.now()
f = open("src/Environment/timestamp.h", "w")
data = str(datetime.timestamp(dt));

f.write(
	"#pragma once \n"
	+ "#include <string.h> \n"
	+ "char compilationTimestampChar[20] = \"" +  data + "\"; \n"
	+ "String compilationTimestampStr = \"" +  data + "\"; \n"
	+ "uint compilationTimestamp = " +  data + "; \n"
)

f.close()

import os
stream = os.popen('git rev-parse --short HEAD')
commit = stream.read()
stream.close()

f = open("src/Environment/compilationdata.h", "w")
data = str(datetime.timestamp(dt));

f.write(
	"#pragma once \n"
	+ "#include <string.h> \n"
	+ "char compilationCommit[10] = \"" + commit.strip() + "\"; \n"
	+ "char compilationDate[20] = \"{0}-{1}-{2} {3}:{4}:{5}\"; \n".format(
		dt.year,
		dt.month,
		dt.day,
		trailingZero(dt.hour),
		trailingZero(dt.minute),
		trailingZero(dt.second)
	)

)

f.close()