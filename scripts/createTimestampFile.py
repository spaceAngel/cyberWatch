from datetime import datetime

dt = datetime.now()
f = open("src/Environment/timestamp.h", "w")
data = str(datetime.timestamp(dt));

f.write(
	"#pragma once \n"
	+ "#include <string.h> \n"
	+ "char compilationTimestampChar[20] = \"" +  data + "\"; \n"
	+ "String compilationTimestampStr = \"" +  data + "\"; \n"
)

f.close()