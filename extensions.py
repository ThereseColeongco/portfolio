file = input("Enter a file name in the format name_of_file.extension : ").lower().strip()

# this extension definition (instead of original file.split(.)[1]) fixes the following errors:
extension = file.split('.')[1:]
str_ext = ' '.join(extension)
'''
:( input of test.txt.pdf, with one extra extension, yields output of application/pdf
    expected "application/pd...", not "text/plain\n"

happens b/c if e.g. extension == "pdf", it will print application/pdf even if after
'''
'''
:( input of myfile, with no extension, yields output of application/octet-stream
    expected "application/oc...", not "Traceback (mos..."

happens b/c
'''
# but b/c it puts everything in a list, even if it's just 1 extension,
# i can't check it against strings like "jpeg", etc.

if len(extension) > 1 or len(extension) == 0:
    print("application/octet-stream")
elif str_ext == "jpeg" or str_ext == "jpg":
    print("image/jpeg")
elif str_ext == "pdf":
    print("application/pdf")
elif str_ext == "png":
    print("image/png")
elif str_ext == "gif":
    print("image/gif")
elif str_ext == "txt":
    print("text/plain")
elif str_ext == "zip":
    print("application/zip")
