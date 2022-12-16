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
from tkinter import Label, Toplevel
from tkinter.ttk import Style
import ttkbootstrap as ttk
from ttkbootstrap.constants import *
from subprocess import call
import os
import subprocess

source=""
def runServeur(): 
    
    subprocess.Popen(["./obj/Serveur",""])
    

    # call(["./Partie2/obj/Serveur"])
   
def runClient(): 
    # a=call(["./Partie2/obj/Client"])
    # print(a)
    global source
    pidClient=subprocess.Popen(["./obj/Client",""]).pid
    print(pidClient)
    source="results/"+str(pidClient)+".txt"
    
def DataEntryForm():
    os.chdir("Partie2")
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
    newWindow.geometry("500x500")
 
    # A Label widget to show in toplevel
    Label(newWindow,
          text ="This is a new window").pack()

    hreadServeur = threading.Thread(target=runServeur, args=()) 
    hreadClient = threading.Thread(target=runClient, args=()) 

    # starting thread 1 
    hreadServeur.start() 
    # starting thread 2 
    hreadClient.start() 
    sleep(0.1)
    print(source)
    f = open(source, "r")
    Label(newWindow,
          text =f.read()).pack()
    



class DataEntry(ttk.Frame):

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
            command=lambda : DataEntryForm(),
            bootstyle=PRIMARY,
            width=65,
        )
        tube_btn.pack(side=TOP, padx=5, pady=5)
        tube_btn.focus_set()

        socket_btn = ttk.Button(
            master=container,
            text="Socket",
            command=self.on_submit,
            bootstyle=SUCCESS,
            width=65,
            
        )
        socket_btn.pack(side=TOP, padx=7, pady=7)
        socket_btn.focus_set()
    # Create style Object
        style = Style()
        
        style.configure('TButton', font =('calibri', 20, 'bold'),
                            borderwidth = '4')

        cnl_btn = ttk.Button(
            master=container,
            text="Cancel",
            command=self.on_cancel,
            bootstyle=DANGER,
            width=65,
            
        )
        cnl_btn.pack(side=BOTTOM, padx=5, pady=5)

    def on_submit(self):
        DataEntryForm()

    def on_cancel(self):
        """Cancel and close the application."""
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

    app = ttk.Window("Data Entry", "superhero", size=(500, 500))
    app.place_window_center()
    DataEntry(app)
    app.mainloop()