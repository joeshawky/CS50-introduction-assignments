class Jar:
    def __init__(self, capacity=12):
        self.__capacity = capacity
        self.__size = 0

    def __str__(self):
        return str(self.size)

    def deposit(self, n):
        self.__size += n

    def withdraw(self, n):
        self.__size -= n

    @property
    def capacity(self):
        return self.__capacity

    @property
    def size(self):
        return self.__size

def main():
    jar = Jar()
    jar.deposit(5)
    jar.withdraw(2)
    print(str(jar.size))


main()
