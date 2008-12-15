#! /usr/bin/env python
import os.path

# search path for dependencies
import sys
sys.path.append(os.path.abspath(os.path.dirname(sys.argv[0]))+"/Main")
sys.path.append(os.path.abspath(os.path.dirname(sys.argv[0]))+"/ConfigBrowser")

from ConfigBrowserPlugin import *
from MainWindow import *

from qt import *

class ConfigBrowserWindow(MainWindow):
    """ MainWindow of EdmBrowser """
    def __init__(self, parent=None, name=None, fl=0):
        """ constructor creates views """
        MainWindow.__init__(self,parent,name,fl)
        self.setCaption("Config Browser")
        self.version="Version of 12.12.2008"
        self.plugins=[ConfigBrowserPlugin(self)]

if __name__ == "__main__":
    app = QApplication(sys.argv)
    f = ConfigBrowserWindow()
    f.show()
    app.setMainWidget(f)

    openfile=""
    for arg in sys.argv[1:]:
        if os.path.exists(arg):
            openfile=arg
            f.plugins[0].openConfigFile(arg)
    import getopt
    try:                                
        opts, args = getopt.getopt(sys.argv[1:], "s:i:", []) 
    except getopt.GetoptError:
        print "python ConfigBrowser.py my_configuration_file.py"                         
        print "-h : print usage summary"                         
        print "-s ... : save screenshot to file (*.bmp,*.png)"                         
        print "-i ... : additional include paths separated by \':\'"                         
        sys.exit(2)    
	
    for opt, arg in opts:                
        if opt in ("-i"):
            i=0
            for path in arg.split(":"):
                sys.path.insert(i,path)
                print "added include path:",path
                i+=1
        if opt in ("-s") and openfile!="":
            f.tabWidget.currentPage().box_view.screenshot(arg)
            print "saved screenshot:",arg
            sys.exit(2)    
    
    app.exec_loop()
