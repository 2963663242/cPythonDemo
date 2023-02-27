import os,json,sys,re
def execCmd(cmd):
    r = os.popen(cmd)
    text = r.readlines()
    r.close()
    return text

def adjust_installName(filename,old,new):
    GET_LIB_INFO = "otool -L %s"
    REGEX = "\t/Library/Frameworks/Python.framework/Versions/3.7/lib/(.+?) \(compatibility "
    CMD = "install_name_tool -change  %s%s %s%s  %s"
    # 获取信息
    text = execCmd(GET_LIB_INFO % filename)

    # 获取名称
    names = []
    for t in text:
        m_obj = re.search(REGEX,t)
        if m_obj is not None:
            LibName = m_obj.group(1)
            names.append(LibName)

    # 构造命令字符串
    for name in  names:
        cmd = CMD % (old,name,new,name,filename)
        print("修改%s的install name %s" % (filename,cmd))
        execCmd(cmd)

if __name__ == "__main__":
    target_dir="/Users/czl/Desktop/st/cPythonDemo/sdk/mac/bin/lib-dynload"
    old = "/Library/Frameworks/Python.framework/Versions/3.7/lib/"
    new = "@loader_path/"

    # 通过文件夹获取文件名
    g = os.walk(target_dir)
    filenames = []
    for path,dir_list,file_list in g:
        for file_name in file_list:
            filenames.append(os.path.join(path, file_name))
    for filename in filenames:
        try:
            adjust_installName(filename,old,new)
        except Exception:
            pass