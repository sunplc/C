
write-record.o: write-record.s linux.s record-def.s
	as write-record.s -o write-record.o

read-record.o: read-record.s linux.s record-def.s
	as read-record.s -o read-record.o

count-chars.o: count-chars.s
	as count-chars.s -o count-chars.o

write-newline.o: write-newline.s linux.s
	as write-newline.s -o write-newline.o

write-records.o: write-records.s linux.s record-def.s
	as write-records.s -o write-records.o

read-records.o: read-records.s linux.s record-def.s
	as read-records.s -o read-records.o

add-year.o: add-year.s linux.s record-def.s
	as add-year.s -o add-year.o

write-identical-records.o: write-identical-records.s linux.s \
	record-def.s
	as write-identical-records.s -o write-identical-records.o

find-largest-age.o: find-largest-age.s linux.s record-def.s
	as find-largest-age.s -o find-largest-age.o

print-error.o: print-error.s linux.s
	as print-error.s -o print-error.o

type-in-a-record.o: type-in-a-record.s linux.s record-def.s
	as type-in-a-record.s -o type-in-a-record.o

search-firstname.o: search-firstname.s linux.s record-def.s
	as search-firstname.s -o search-firstname.o

write-records: write-record.o write-records.o
	ld write-record.o write-records.o -o write-records

read-records: count-chars.o write-newline.o read-record.o \
	read-records.o
	ld count-chars.o write-newline.o read-record.o \
		read-records.o -o read-records

add-year: add-year.o read-record.o write-record.o print-error.o
	ld add-year.o read-record.o write-record.o print-error.o \
		-o add-year

write-identical-records: write-identical-records.o \
	write-record.o
	ld write-identical-records.o write-record.o -o \
		write-identical-records

find-largest-age: find-largest-age.o read-record.o
	ld find-largest-age.o read-record.o -o find-largest-age

type-in-a-record: type-in-a-record.o print-error.o count-chars.o
	ld type-in-a-record.o print-error.o count-chars.o \
	-o type-in-a-record

search-firstname: count-chars.o write-newline.o read-record.o \
	search-firstname.o
	ld count-chars.o write-newline.o read-record.o \
		search-firstname.o -o search-firstname

