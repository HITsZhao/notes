/*
 *关于C++ 智能指针的使用 <memory>
 * focus: 1.如何使用智能指针；2.智能指针替代new/delete管理动态内存方案
 * */

//如何使用shared_ptr
//	1.什么是shared_ptr
//		shared_ptr是一个用于管理资源的类。资源包括：内存，连接等
//		shared_ptr适合于管理需要手动分配和释放的资源，程序自动管理的资源（比如局部变量，静态变量）没必要（也不适合）使用shared_ptr
//		shared_ptr<T> name:
//			T: 智能指针指向的类型：
//				i.e. 
//					shared_ptr<int> p(new int(10)); // 基本数据类型
//					shared_ptr<X> px(new X());		// 类
//					connection c = connection();	// 资源，如打开文件，网络连接，数据库连接等
//					shared_ptr<connection> pc(&c,end_connection); //可以传入deletor 用于自动释放资源
//			name:
//				name(U*p,Del):利用此构造函数可以传入自定义的删除操作
//		shared_ptr重载了'.'和'->'操作符，使得shared_ptr类的使用与普通指针非常类似

//	2.如何使用shared_ptr
//		不要混合使用智能指针和普通指针
//		建议使用make_shared<T>()替代new
//
//		创建shared_ptr(对比)
		//普通指针										// shared_ptr
		int *p = NULL;/*空指针*/						std::shared_ptr<int> p;/*空的shared_ptr类*/
		int *p = new Class();/*在堆中申请资源*/			std::shared_ptr<Class> p = make_shared<Class>();/*make_shared函数在动态内存（堆）中分配一个对象并按照函数的参数初始化该对象，返回此对象的shared_ptr*/
		int *q = p;/*p和q指向同一个地址*/				std::shared_ptr<int> q(p);/*类的构造函数形式*/ 
														std::shared_ptr<int> q = p /*p指向的对象的引用计数+1，q指向的对象的引用计数-1，如果该对象引用计数==0,那么释放该对象（不是释放q）*/

//	3. shared_ptr的原理：
//		shared_ptr实例所指向的对象（内存或资源）的引用计数==0时，当shared_ptr生命周期结束时，会在析构自身的同时，完成对所指向对象资源的释放工作
//		shared_ptr实例本身有可能是局部变量或类的成员变量，其自身生命周期结束时，会使得所指向的对象的引用计数-1,当所指向的对象的引用计数==0时，才会释放资源，否则，只析构自身
//
// 4. shared_ptr的构造函数：
// 	在shared_ptr可以通过这几种构造（一种或多种）:construct from [[[pointer] + deleter] + allocator]
// 	如果pointer,deleter,allocator 三个都没有：那么生成的是empty类型的shared_ptr;
// 	如果只有pointer，那么生成的shared_ptr与pointer指向同一处资源;
// 	如果是pointer和deleter：那么在shared_ptr指向的资源引用计数为0的时候，shared_ptr析构函数调用deleter；常用于释放文件，连接等资源
// 	如果是pointer,delter,allocator,那么，除了析构调用deleter以外，在创建的时候，会调用allocator分配资源

// 5. shared_ptr使用注意事项：
// 	（1）“不要普通指针和智能指针混用”，这句话是指的“普通指针”是指向动态申请的资源（比如堆中申请的内存）的指针。对于局部变量，或者静态变量，当使用普通指针初始化智能指针的时候，会出现delete局部变量的错误
//	（2）使用make_shared()函数替代new来分配动态内存，可以很大程度上避免普通指针再次指向该内存空间(因为如果要拷贝该指针，必须是shared_ptr对象)
//	（3）格外注意普通指针和智能指针存在转换的函数:1.普通指针转智能指针shared_ptr构造函数std::shared_ptr<T>(U*p),2.智能指针转普通指针shared_ptr.get()


//如何使用weak_ptr
// 1.why weak_ptr? 为什么我们需要weak_ptr
// 		weak_ptr是shared_ptr循环引用问题的一个“补丁”，在可以预见的循环引用的问题上，使用weak_ptr。（当然，一般出现循环引用，优先从设计结构上去解决）
// 2. what is weak_ptr? 什么是weak_ptr？
// 	 weak 和 strong 相对：strong是指，该指针会改变对象的引用计数，且会负责检查和释放资源；weak 是指，该指针不会改变引用计数，且不控制资源的释放
// 	 所以:weak_ptr是一种不控制所指向对象生存期的智能指针，它指向一个shared_ptr管理的对象。weak_ptr不改变引用计数，shared_ptr释放资源时不考虑weak_ptr的绑定.
// 	 从上面可以看出，weak_ptr是一种依赖于shared_ptr的类型，所以，可以推测，其只能用shared_ptr和weak_ptr来初始化
//
// 3. How to use weak_ptr? 如何使用weak_ptr？
// 	（1）初始化
		weak_ptr(T) wp(sp);//使用shared_ptr初始化
		weak_ptr(T) wp = w;//使用weak_ptr初始化
//	（2）获取weak_ptr绑定对象的shared_ptr
		weak_ptr.lock(); //由于weak_ptr的弱引用特点，资源释放时，不会考虑weak_ptr，所以，在通过weak_ptr获取对象的sheared_ptr时，需要调用lock()函数，该函数会校验weak_ptr指向的对象是否存在，如果存在,则返回一个指向共享对象的shared_ptr，如果不存在，返回一个empty shared_ptr
		if(shared_ptr<int> np = wp.lock()){
			//如果wp指向的对象没有被释放，则np不为空，np指向wp绑定的对象
		}



