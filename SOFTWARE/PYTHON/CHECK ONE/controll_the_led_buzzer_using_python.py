# control the led using gui application 




import customtkinter
import serial
import pyttsx3



# define the background themes 
customtkinter.set_appearance_mode("dark")
customtkinter.set_default_color_theme("green")

engine = pyttsx3.init()

# define the serial module to communicate the arduino
arduino_port = 'COM13'

SerialMonitor = serial.Serial(arduino_port , 9600 , timeout = 1)
window = customtkinter.CTk()

# define the function for text to speech 
def speak(voices):
    engine.say(voices)
    engine.runAndWait()

# first led 
def first_button_value ():
    speak("first button pressed ")
    SerialMonitor.write(b'a')
    print("first led on ")

def second_button_value ():
    speak("second button pressed ")
    SerialMonitor.write(b'b')
    print("first led off ")

# second led 
def third_button_value ():
    speak("third button pressed ")
    SerialMonitor.write(b'c')
    print("second led on ")

def fourth_button_value ():
    speak("fourth button pressed ")
    SerialMonitor.write(b'd')
    print("second led off ")

# third led 
def fifth_button_value ():
    speak("fifth button pressed ")
    SerialMonitor.write(b'e')
    print("buzzer on  ")

def six_button_value ():
    speak("six button pressed ")
    SerialMonitor.write(b'f')
    print("buzzer off  ")

# define the window size 
window.geometry("500x500")

# define the window heading 
window.title("pie.space")

# create a label 
first_lavel = customtkinter.CTkLabel(window , text= "CONTROL THE LED USING GUI APPLICATION ")
first_lavel .grid(padx = 10 , pady =10 , row = 0 , column =0 )

# create a frame and inside the frame create a button 
first_frame = customtkinter.CTkFrame(window , height = 200 , width= 200)
first_frame.grid(padx = 5 , pady = 5 , row = 1 , column = 0 )

# define the button 
# define the first button 
first_button = customtkinter.CTkButton(first_frame , text= "FIRST LED ON " , command= first_button_value)
first_button.grid(padx = 5 , pady = 5 , row = 2 , column = 0 )

# define the second led 
second_button = customtkinter.CTkButton(first_frame , text=" FIRST LED OFF " , command= second_button_value)
second_button.grid(padx = 5 , pady = 5 , row = 2 , column = 1 )

# define the third  led 
third_button = customtkinter.CTkButton(first_frame , text=" SECOND LED ON  " , command= third_button_value)
third_button.grid(padx = 5 , pady = 5 , row = 3 , column = 0 )


# define the FOURTH  led 
fourth_button = customtkinter.CTkButton(first_frame , text=" SECOND LED OFF " , command= fourth_button_value)
fourth_button.grid(padx = 5 , pady = 5 , row = 3 , column = 1 )


# define the fifth led 
fifth_button = customtkinter.CTkButton(first_frame , text=" THIRD LED ON  " , command= fifth_button_value)
fifth_button.grid(padx = 5 , pady = 5 , row = 4 , column = 0 )

# define the FIFTH led 
fifth_button = customtkinter.CTkButton(first_frame , text=" THIRD LED OFF " , command= six_button_value)
fifth_button.grid(padx = 5 , pady = 5 , row = 4 , column = 1 )

# define the window mainloop
window.mainloop()

# close the serial monitor
SerialMonitor.close()

