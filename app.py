# import ttkbootstrap as ttk
# from ttkbootstrap.constants import *

# root = ttk.Window(themename="superhero")

# b1 = ttk.Button(root, text="Submit", bootstyle="success")
# b1.pack(side=LEFT, padx=5, pady=10)

# b2 = ttk.Button(root, text="Submit", bootstyle="info-outline")
# b2.pack(side=LEFT, padx=5, pady=10)

# root.mainloop()

import threading
from time import sleep
from tkinter import *
from tkinter.ttk import Style, Treeview
import ttkbootstrap as ttk
from ttkbootstrap.constants import *
from subprocess import call
import os, signal
import subprocess

source=""
pidServeurSocket=0
pidServeurTube=0
def runServeur(): 
    global pidServeurSocket
    pidServeurSocket=subprocess.Popen(["./obj/Serveur",""]).pid
    print("aaaaaaaaaaa "+str(pidServeurSocket))

    # call(["./Partie2/obj/Serveur"])
   
def runClient(): 
    # a=call(["./Partie2/obj/Client"])
    # print(a)
    global source
    pidClient=subprocess.Popen(["./obj/Client",""]).pid
    print(pidClient)
    source="results/"+str(pidClient)+".txt"

def runServeurTube():  
    global pidServeurSocket
    pidServeurSocket=subprocess.Popen(["./obj/Serveur",""]).pid

def runClientTube(): 
    global source
    pidClient=subprocess.Popen(["./obj/Client",""]).pid
    print(pidClient)
    source="results/"+str(pidClient)+".txt"
    
def SocketResult():
    osPath=str(os.getcwd())
    if ((osPath).__contains__("Partie1")):
        os.chdir("..")
    osPath=str(os.getcwd())
    if not( (osPath).__contains__("Partie2")):
        os.chdir("Partie2")
        osPath=str(os.getcwd())
   # Toplevel object which will
    # be treated as a new window
    newWindow = Toplevel(app)
  
    # sets the title of the
    # Toplevel widget
    newWindow.title("Socket")
    newWindow.update_idletasks()
    w_height = newWindow.winfo_height()
    w_width = newWindow.winfo_width()
    s_height = newWindow.winfo_screenheight()
    s_width = newWindow.winfo_screenwidth()
    xpos = (s_width - w_width) // 2
    ypos = (s_height - w_height) // 2
    newWindow.geometry(f'+{xpos}+{ypos}')
    # sets the geometry of toplevel
    newWindow.geometry("500x450")
 


    hreadServeur = threading.Thread(target=runServeur, args=()) 
    hreadClient = threading.Thread(target=runClient, args=()) 

    # starting thread 1 
    hreadServeur.start() 
    # starting thread 2 
    hreadClient.start() 
    sleep(0.2)
    print(source)
    f = open(source, "r")
    # Label(newWindow,
    #       text =f.read()).pack()
    
    labelframe1=ttk.LabelFrame(newWindow, text="Message de client",bootstyle="info")
    labelframe1.pack(fill="both", padx=20, pady=20, expand="yes")
    left_frame  =  Frame(labelframe1,  width=200,  height=  400)
    left_frame.pack( padx=10,  pady=10)
    right_frame  =  Frame(labelframe1,  width=200,  height=400)
    right_frame.pack(   padx=10,  pady=10)
    
    Label(left_frame, text="Pid de client:").pack(ipadx=20, ipady=20, fill=BOTH, expand=True, side=LEFT)
    Label(left_frame, text=str(f.readline().strip()),justify=LEFT).pack(ipadx=20, ipady=20, fill=BOTH, expand=True, side=RIGHT)
    Label(right_frame, text="Number:").pack(ipadx=20, ipady=20, fill=BOTH, expand=True, side=LEFT)
    nb=int(f.readline().strip())
    Label(right_frame, text=str(nb),justify=LEFT).pack(ipadx=20, ipady=19, fill=BOTH, expand=True, side=RIGHT)

    labelframe2=ttk.LabelFrame(newWindow, text="Réponse de serveur",bootstyle="info")
    labelframe2.pack(fill="both", padx=20, pady=20, expand="yes")
    left_frame  =  Frame(labelframe2,  width=200,  height=  400)
    left_frame.pack( padx=10,  pady=10)
    right_frame  =  Frame(labelframe2,  width=200,  height=400)
    right_frame.pack(   padx=10,  pady=10)
    right_frame1  =  Frame(labelframe2,  width=200,  height=400)
    right_frame1.pack(   padx=10,  pady=10)
    
    Label(left_frame, text="Pid de serveur:").pack(ipadx=15, ipady=20, fill=BOTH, expand=True, side=LEFT)
    Label(left_frame, text=str(f.readline().strip()),justify=LEFT).pack(ipadx=20, ipady=20, fill=BOTH, expand=True, side=RIGHT)
    Label(right_frame, text="Tableau:").pack(ipadx=20, ipady=20, fill=BOTH, expand=True, side=LEFT)
    for i in range(nb):
        Label(right_frame, text="| "+str(f.readline().strip()),justify=LEFT).pack(ipadx=4, ipady=4, fill=BOTH, expand=True, side=RIGHT)

def TubeResult():

    osPath=str(os.getcwd())
    print(osPath)
    if ((osPath).__contains__("Partie2")):
        os.chdir("..")
    osPath=str(os.getcwd())
    print(osPath)
    if not( (osPath).__contains__("Partie1")):
        os.chdir("Partie1")
        osPath=str(os.getcwd())
    
   # Toplevel object which will
    # be treated as a new window
    newWindow = Toplevel(app)
  
    # sets the title of the
    # Toplevel widget
    newWindow.title("Tubes nommées")
    newWindow.update_idletasks()
    w_height = newWindow.winfo_height()
    w_width = newWindow.winfo_width()
    s_height = newWindow.winfo_screenheight()
    s_width = newWindow.winfo_screenwidth()
    xpos = (s_width - w_width) // 2
    ypos = (s_height - w_height) // 2
    newWindow.geometry(f'+{xpos}+{ypos}')
    # sets the geometry of toplevel
    newWindow.geometry("500x450")


    hreadServeurTube = threading.Thread(target=runServeurTube, args=()) 
    hreadClientTube = threading.Thread(target=runClientTube, args=()) 

    # starting thread 1 
    hreadServeurTube.start() 
    # starting thread 2 
    hreadClientTube.start() 
    sleep(0.1)
    print(source)
    f = open(source, "r")
    
    labelframe1=ttk.LabelFrame(newWindow, text="Message de client",bootstyle="info")
    labelframe1.pack(fill="both", padx=20, pady=20, expand="yes")
    left_frame  =  Frame(labelframe1,  width=200,  height=  400)
    left_frame.pack( padx=10,  pady=10)
    right_frame  =  Frame(labelframe1,  width=200,  height=400)
    right_frame.pack(   padx=10,  pady=10)
    
    Label(left_frame, text="Pid de client:").pack(ipadx=20, ipady=20, fill=BOTH, expand=True, side=LEFT)
    Label(left_frame, text=str(f.readline().strip()),justify=LEFT).pack(ipadx=20, ipady=20, fill=BOTH, expand=True, side=RIGHT)
    Label(right_frame, text="Number:").pack(ipadx=20, ipady=20, fill=BOTH, expand=True, side=LEFT)
    nb=int(f.readline().strip())
    Label(right_frame, text=str(nb),justify=LEFT).pack(ipadx=20, ipady=19, fill=BOTH, expand=True, side=RIGHT)

    labelframe2=ttk.LabelFrame(newWindow, text="Réponse de serveur",bootstyle="info")
    labelframe2.pack(fill="both", padx=20, pady=20, expand="yes")
    left_frame  =  Frame(labelframe2,  width=200,  height=  400)
    left_frame.pack( padx=10,  pady=10)
    right_frame  =  Frame(labelframe2,  width=200,  height=400)
    right_frame.pack(   padx=10,  pady=10)
    right_frame1  =  Frame(labelframe2,  width=200,  height=400)
    right_frame1.pack(   padx=10,  pady=10)
    
    Label(left_frame, text="Pid de serveur:").pack(ipadx=20, ipady=20, fill=BOTH, expand=True, side=LEFT)
    Label(left_frame, text=str(f.readline().strip()),justify=LEFT).pack(ipadx=20, ipady=20, fill=BOTH, expand=True, side=RIGHT)
    Label(right_frame, text="Tableau:").pack(ipadx=20, ipady=20, fill=BOTH, expand=True, side=LEFT)
    for i in range(nb):
        Label(right_frame, text="| "+str(f.readline().strip()),justify=LEFT).pack(ipadx=4, ipady=4, fill=BOTH, expand=True, side=RIGHT)




class Bienvenu(ttk.Frame):

    def __init__(self, master):
        super().__init__(master, padding=(20, 10))
        self.pack(fill=BOTH, expand=YES)
        self.create_buttons()
    
    def create_buttons(self):
        """Create the application buttonbox"""
        container = ttk.Frame(self)
        container.pack(fill=X, expand=YES, pady=(15, 10))

        tube_btn = ttk.Button(
            master=container,
            text="Tube nommée",
            command=lambda : TubeResult(),
            #bootstyle=PRIMARY,
            bootstyle="primary-outline",
            #bg="#009FFF",
            width=65,
        )
        tube_btn.pack(side=TOP,ipadx=10, ipady=10, padx=10, pady=10,fill=BOTH)
        tube_btn.focus_set()

        socket_btn = ttk.Button(
            master=container,
            text="Socket",
            command=lambda : SocketResult(),
            bootstyle="success-outline",
            #bg="#00EAB9",
            width=65, 
            
        )
        socket_btn.pack(ipadx=10, ipady=10, padx=10, pady=10,fill=BOTH)
        socket_btn.focus_set()
    # Create style Object
        style = Style()
        
        style.configure('TButton', font =('calibri', 20, 'bold'),
                            borderwidth = '4')

        cnl_btn = ttk.Button(
            master=container,
            text="Fermer",
            command=self.on_cancel,
            bootstyle="danger-outline",
            #bootstyle=DANGER,
            #bg="#FF1851",
            width=65,
            
        )
        cnl_btn.pack(side=BOTTOM,ipadx=10, ipady=10, padx=10, pady=10,fill=BOTH)

    def on_submit(self):
        SocketResult()

    def on_cancel(self):
        """Cancel and close the application."""
        os.system("lsof -i:9000 | grep LISTEN | tr -s ' ' | cut -d' ' -f2 | xargs kill -9")
        os.system("kill -2 "+str(pidServeurTube))
        self.quit()
    def place_window_center(self):
        """Position the toplevel in the center of the screen. Does not
        account for titlebar height."""
        self.update_idletasks()
        w_height = self.winfo_height()
        w_width = self.winfo_width()
        s_height = self.winfo_screenheight()
        s_width = self.winfo_screenwidth()
        xpos = (s_width - w_width) // 2
        ypos = (s_height - w_height) // 2
        self.geometry(f'+{xpos}+{ypos}')

    position_center = place_window_center # alias



if __name__ == "__main__":
    app = ttk.Window("Data Entry", "superhero", size=(500, 450)) 
    app.place_window_center()
    Bienvenu(app)
    app.mainloop()