 ///
 /// @file    Message.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2018-09-16 18:46:50
 ///
 
#ifndef __WD_34_H
#define __WD_34_H
#include <set>
#include <string>
class Folder;
class Message
{
	friend void swap(Message &,Message &);
	friend class Folder;
public:
	explicit Message(const std::string &str="")
	:contents(str){}
	Message(const Message &);//复制构造函数
	Message &operator=(const Message  &);//赋值运算符函数
	~Message();//析构函数
	//save()和remove()向一个给定的目录添加一条Message或
	//从中删除一条Message
	void save(Folder &);
	void remove(Folder &);
	void print_debug();
private:
	std::string contents;
	std::set<Folder*> folders;//目录容器
	void add_to_Folders(const Message &);
	void remove_from_Folders();
	void addFldr(Folder *f)
	{folders.insert(f);}
	void remFldr(Folder *f)
	{folders.erase(f);}
};
void swap(Message &,Message &);
class Folder
{
	friend void swap(Folder &,Folder &);
	friend class Message;
public:
	Folder()=default;
	Folder(const Folder &);
	Folder &operator=(const Folder &);
	~Folder();

	void print_debug();
private:
	std::set<Message *> msgs;//消息容器

	void add_to_Message(const Folder &);
	void remove_from_Message();

	void addMsg(Message *m)//向邮件中添加内容
	{msgs.insert(m);}
	void remMsg(Message *m)//删除邮件中的内容
	{msgs.erase(m);}
};
void swap(Folder &,Folder &);
#endif
