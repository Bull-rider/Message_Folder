 ///
 /// @file    34.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-17 16:02:10
 ///
#include "34.h"
#include <iostream>
void Message::save(Folder &f)
{
	addFldr(&f);//把邮件所在目录指针插入到Folder类型的set容器中
	f.addMsg(this);//把邮件指针插入到Message类型的set容器中
}
void Message::remove(Folder &f)
{
	remFldr(&f);
	f.remMsg(this);
}

//Message的拷贝控制成员
void Message::add_to_Folders(const Message &m)
{
	for(auto f:m.folders)//循环拿到每一个包含Message对象指针的Folder对象
		f->addMsg(this);//在每个Folder对象中添加一个Message指针
}
Message::Message(const Message &m)
:contents(m.contents)
,folders(m.folders)
{
	add_to_Folders(m);//在每个包含此消息的Folder中添加一个指向新对象的
}						//指针

//Mesage的析构函数
void Message::remove_from_Folders()
{
	for(auto f:folders)
	{
		f->remMsg(this);
	}
}

Message::~Message()
{
	remove_from_Folders();
}
//Message的赋值运算符函数
Message &Message::operator=(const Message &rhs)
{
	remove_from_Folders();
	contents=rhs.contents;
	folders=rhs.folders;
	add_to_Folders(rhs);
	return *this;
}
//Message的swap函数
void swap(Message &lhs,Message &rhs)
{
	using std::swap;
	lhs.remove_from_Folders();
	rhs.remove_from_Folders();

	swap(lhs.folders,rhs.folders);
	swap(lhs.contents,rhs.contents);

	lhs.add_to_Folders(lhs);
	rhs.add_to_Folders(rhs);
}
void Message::print_debug()
{
	std::cout<<contents<<std::endl;
}
//------Folder Implementation
void Folder::add_to_Message(const Folder &f)//在目录中添加邮件
{
	for(auto m:f.msgs)//循环拿到包含包含Folder对象指针的Message对象
		m->addFldr(this);//把Folder指针添加到每一个Message对象中
}
Folder::Folder(const Folder &f)//目录复制时要把邮件全部拷贝
:msgs(f.msgs)
{
	add_to_Message(f);
}
void Folder::remove_from_Message()
{
	for(auto m:msgs)
		m->remFldr(this);
}

Folder::~Folder()
{
	remove_from_Message();
}

Folder &Folder::operator=(const Folder &rhs)
{
	remove_from_Message();
	msgs=rhs.msgs;
	add_to_Message(rhs);
	return *this;
}

void Folder::print_debug()
{
	for(auto m:msgs)
		std::cout<<m->contents<<" ";
	std::cout<<std::endl;
}
void swap(Folder &lhs,Folder &rhs)
{
	using std::swap;
	lhs.remove_from_Message();
	rhs.remove_from_Message();

	swap(lhs.msgs,rhs.msgs);

	lhs.add_to_Message(lhs);
	rhs.add_to_Message(rhs);
}
int main()
{
	return 0;
}
