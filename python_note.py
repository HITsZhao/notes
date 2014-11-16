#!/usr/bin/env python
#-*- coding: utf-8 -*-

#	Python 的with语句

#1. why with? 为什么要引入with语句

#	python2.6版本开始引入with语句。with语句用于解决异常发生时的资源释放的问题
#	with语句适用于对资源进行访问的场合，确保不管使用过程中是否发生异常，都会执行
#	必要的清理工作，确保资源的释放（例如，文件使用后自动关闭，线程中锁的自动获取和释放）

#2. 术语
#	（1）上下文管理协议（Context Management Protocol）:
#		该协议是指，支持协议的对象需要实现__enter__()和__exit__()两个方法，在__enter__()中
#		获取资源，在__exit__()中释放资源
#	（2）上下文管理器（Context Manager）:实现上下文协议的对象。
#		这种对象实现了__enter__()和__exit__方法。通常使用with语句调用上下文管理器。

#3.基本语法格式
#	with Context_Manager [as target(s)]:
#		with-body

#	基本语法的解释: 如果指定as 语句，那么Context_Manager的__enter__()方法的返回值将赋给target(s)
#					target可以是单个变量也可以是tuple

#4.工作原理
#	with的工作方式类似于try/except/finally，但是对比而言with语句更加简洁有力
#	(1) 使用with语句操作文件对象
		with open(r'somefileName') as somefile:
			for line in somefile:
				pass

#	(2) 使用try/except/finally语句操作文件对象：
		somefile = open(r"somefileName")
		try:
			for line in somefile:
				pass
		finally:
			somefile.close()
#	上述两种方式都实现了打开文件-->操作-->关闭文件的功能，with语句的代码量更少，表达更简洁
#	Python的一些内建对象实现了上下文协议，例如文件对象，此外支持上下文管理协议的模块还有threading、decimal等。
#	

#5.自定义上下文管理器
#	可以自定义实现了上下文协议的上下文管理器，方法就是实现上下文协议规定的__enter__()和__exit__()两个方法：
#	（1）__enter__():
#		获取资源。如果with语句中定义了as 对象的话，该函数的返回值将赋给该对象
#	（2）__exit__(exc_type, exc_value, exc_traceback):
#		exc_type表示异常类型，exc_value表示异常值，exc_traceback表示异常堆栈
#		释放资源。如果没有发生异常，则exc_type, exc_value, exc_traceback 都为None，否则，表示发生异常；
#		函数的返回值用于表示是否对发生的异常进行处理，返回值为True表示不处理异常，返回值为False表示重新抛出异常
#		由with语句以外的代码处理
#	可以自定义上下文管理器来对系统的资源进行管理，比如数据库连接，共享资源的访问控制等


