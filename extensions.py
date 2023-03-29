file = input("Enter a file name in the format name_of_file.extension : ").lower().strip()

# this extension definition (instead of original file.split(.)[1]) fixes the following errors:
extension = file.split('.')[-1]

if extension == "jpeg" or extension == "jpg":
    print("image/jpeg")
elif extension == "pdf":
    print("application/pdf")
elif extension == "png":
    print("image/png")
elif extension == "gif":
    print("image/gif")
elif extension == "txt":
    print("text/plain")
elif extension == "zip":
    print("application/zip")
else:
    print("application/octet-stream")