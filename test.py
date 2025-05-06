class Book():
    def __init__(self, name, writer, num=1):
        self.__name = name
        self.__writer = writer
        self.__number_of_books = num  

    def add(self, num=1):
        self.__number_of_books += num

    def remove(self):
        if self.__number_of_books > 0:
            self.__number_of_books -= 1

    def get_name(self):
        return self.__name

    def get_writer(self):
        return self.__writer
    
    
    def count(self):
        return self.__number_of_books

    def __str__(self):
        return f"Name = {self.__name}, Writer = {self.__writer}, Count = {self.__number_of_books}"


books = []

while True:
    line = input() 
    if line == '#':
        break
    parts = line.split()
    
    
    if parts[0] == "new" :
            name = parts[1]
            writer = parts[2]
            num = int(parts[3])
            new_book = Book(name, writer, num)
            books.append(new_book)
            print("confirmed")
            
            
            
    elif parts[0]=="take":
        name = parts[1]
        writer = parts[2]
        flag = False
        for book in books:
            if book.get_name()==name and book.get_writer()==writer:
                flag=True
                if book.count()>0:
                    print("here you go ,%s"%(book.count()))
                    book.remove()
                    break
                else :
                    print("come back later please")
                    break
        
        if flag!=True:
            print( "sorry we don't have that book")
            
    elif parts[0]=="give":
        name = parts [1]
        writer = parts[2]
        flag = False 
        for book in books :
            flag =True
            if book.get_name()==name and book.get_writer()==writer:
                book.add()
                print("accepted")
                
        if flag == False :
            print ("wrong library ")
            
                  

print ("test")
print ("test")