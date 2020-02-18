//https://leetcode.com/problems/print-in-order/discuss/335939/5-Python-threading-solutions-(Barrier-Lock-Event-Semaphore-Condition)-with-explanation

//Runtime: 28 ms, faster than 96.04% of Python3 online submissions for Print in Order.
//Memory Usage: 13.1 MB, less than 100.00% of Python3 online submissions for Print in Order.

from threading import Barrier

class Foo:
    def __init__(self):
        self.first_barrier = Barrier(2)
        self.second_barrier = Barrier(2)

    def first(self, printFirst: 'Callable[[], None]') -> None:
        
        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self.first_barrier.wait()


    def second(self, printSecond: 'Callable[[], None]') -> None:
        self.first_barrier.wait()
        # printSecond() outputs "second". Do not change or remove this line.
        printSecond()
        self.second_barrier.wait()


    def third(self, printThird: 'Callable[[], None]') -> None:
        self.second_barrier.wait()
        # printThird() outputs "third". Do not change or remove this line.
        printThird()

//Runtime: 40 ms, faster than 59.25% of Python3 online submissions for Print in Order.
//Memory Usage: 13.1 MB, less than 100.00% of Python3 online submissions for Print in Order.

from threading import Lock

class Foo:
    def __init__(self):
        self.locks = (Lock(), Lock())
        self.locks[0].acquire()
        self.locks[1].acquire()

    def first(self, printFirst: 'Callable[[], None]') -> None:
        
        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self.locks[0].release()

    def second(self, printSecond: 'Callable[[], None]') -> None:
        
        # printSecond() outputs "second". Do not change or remove this line.
        with self.locks[0]:
            printSecond()
            self.locks[1].release()


    def third(self, printThird: 'Callable[[], None]') -> None:
        
        # printThird() outputs "third". Do not change or remove this line.
        with self.locks[1]:
            printThird()

//Runtime: 40 ms, faster than 59.25% of Python3 online submissions for Print in Order.
//Memory Usage: 13.1 MB, less than 100.00% of Python3 online submissions for Print in Order.

from threading import Event

class Foo:
    def __init__(self):
        self.done = (Event(), Event())

    def first(self, printFirst: 'Callable[[], None]') -> None:
        
        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self.done[0].set()


    def second(self, printSecond: 'Callable[[], None]') -> None:
        
        # printSecond() outputs "second". Do not change or remove this line.
        self.done[0].wait()
        printSecond()
        self.done[1].set()


    def third(self, printThird: 'Callable[[], None]') -> None:
        
        # printThird() outputs "third". Do not change or remove this line.
        self.done[1].wait()
        printThird()

/Runtime: 44 ms, faster than 44.53% of Python3 online submissions for Print in Order.
//Memory Usage: 13 MB, less than 100.00% of Python3 online submissions for Print in Order.

from threading import Semaphore

class Foo:
    def __init__(self):
        self.gates = (Semaphore(0), Semaphore(0))


    def first(self, printFirst: 'Callable[[], None]') -> None:
        
        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self.gates[0].release()


    def second(self, printSecond: 'Callable[[], None]') -> None:
        
        # printSecond() outputs "second". Do not change or remove this line.
        with self.gates[0]:
            printSecond()
            self.gates[1].release()


    def third(self, printThird: 'Callable[[], None]') -> None:
        
        # printThird() outputs "third". Do not change or remove this line.
        with self.gates[1]:
            printThird()

//Runtime: 44 ms, faster than 44.53% of Python3 online submissions for Print in Order.
//Memory Usage: 13 MB, less than 100.00% of Python3 online submissions for Print in Order.

from threading import Condition

class Foo:
    def __init__(self):
        self.exec_condition = Condition()
        self.order = 0
        self.first_finish = lambda : self.order == 1
        self.second_finish = lambda : self.order == 2

    def first(self, printFirst: 'Callable[[], None]') -> None:
        
        # printFirst() outputs "first". Do not change or remove this line.
        with self.exec_condition:
            printFirst()
            self.order = 1
            self.exec_condition.notify(2)


    def second(self, printSecond: 'Callable[[], None]') -> None:
        
        # printSecond() outputs "second". Do not change or remove this line.
        with self.exec_condition:
            self.exec_condition.wait_for(self.first_finish)
            printSecond()
            self.order = 2
            self.exec_condition.notify()


    def third(self, printThird: 'Callable[[], None]') -> None:
        
        # printThird() outputs "third". Do not change or remove this line.
        with self.exec_condition:
            self.exec_condition.wait_for(self.second_finish)
            printThird()
