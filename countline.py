import os

directory = ['core', 'world']


def count_file_line(filepath):
    with open(filepath) as f:
        return len(f.readlines())


total_line_count = 0
for path in directory:
    for p in os.walk(path):
        prefix = p[0]
        files = p[2]
        for file in files:
            fullpath = os.path.join(prefix, file)

            cnt = count_file_line(fullpath)
            total_line_count += cnt
            print(fullpath, cnt)

    print("----------")

print("total:", total_line_count)
