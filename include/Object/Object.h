//--------------------------------------------------------------------------------------------
//  �쐬�� : �A�R����
//
//  �X�V����  �F2014.09.30  Ver1.00  �A�R����  ��{�I�ȋ@�\�̎���
//              2015.05.28  Ver1.01  �A�R����  renderWithChildren()��virtual�ɂ���
//                                             postMsg receiveMsg�Ƀ|�C���^�ł��쐬����
//--------------------------------------------------------------------------------------------
#pragma once

#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <functional>
#include <assert.h>


//-----------------------------------------------------------------------
//�L���X�g�֘A
//-----------------------------------------------------------------------
//weak_ptr����C�ӂ̌^�ւ�shared_ptr�փL���X�g���܂�
template<typename T1, typename T2>
inline std::shared_ptr<T1> weak_to_shared(const std::weak_ptr<T2>& ptr)
{
	if (ptr.expired()) return std::shared_ptr<T1>();
	return std::static_pointer_cast<T1>(ptr.lock());
}
//weak_ptr���瓯���^�ւ�shared_ptr�փL���X�g���܂�
template<typename T>
inline std::shared_ptr<T> weak_to_shared(const std::weak_ptr<T>& ptr)
{
	if (ptr.expired()) return std::shared_ptr<T>();
	return std::static_pointer_cast<T>(ptr.lock());
}
//shared_ptr����Ⴄ�^�ւ�shared_ptr�փL���X�g���܂�
template<typename T1, typename T2>
inline std::shared_ptr<T1> shared_cast(const std::shared_ptr<T2>& ptr)
{
	return std::static_pointer_cast<T1>(ptr);
}

//-----------------------------------------------------------------------
//�x�[�X�I�u�W�F�N�g
//-----------------------------------------------------------------------
class Object
{
public:
	enum class Status
	{
		null,    //����`
		run,     //���쒆
		sleep,   //��~���A�K��t���[����run�ɕω�
		pause,   //�|�[�Y���iupdate()�ł͂Ȃ�updatePause()�������j
		destroy, //�j���҂�
		dead,    //�폜
	};

	//�I�u�W�F�N�g����
	//�p�����ɌĂяo���A���O�Ƌ쓮�X�e�[�^�X��ݒ肷�邱��
	Object(
		const std::string& name,
		Status status = Status::run)
		:
		name_(name),
		status_(status),
		priority_(0),
		framecount_(0),
		hierarchyLevel_(1)
	{
		//      OutputDebugString("Object\n");
		initID();
	}

	//�I�u�W�F�N�g�j���A���ɉ������Ȃ���virtual�ɂ��Ă����Ȃ��ƃ��[�N���N����\��������
	virtual ~Object()
	{
		//      OutputDebugString("~Object\n");
		//      DeleteStringFromList(id_);
		//      std::ofstream f("a.txt", std::ofstream::app);
		//      f << "destractor:" << name_ << std::endl;
	}

	//-----------------------------------------------------------------------
	//�e�ɃI�u�W�F�N�g��ǉ�
	//-----------------------------------------------------------------------
	template<typename Ptr>
	std::weak_ptr<Object> insertToParent(Ptr* o)
	{
		auto parent = getParentPtr();
		if (parent.expired())
			assert(!"�e�̃|�C���^������܂����");
		parent.lock()->insertAsChild(o);
		return o->selfPtr();
	}
	//�|�[�Y��ԂŐe�ɒǉ�
	template<typename Ptr>
	std::weak_ptr<Object> insertToParentPause(Ptr* o)
	{
		std::weak_ptr<Object> ret = insertToParent(o);
		o->pause();
		return ret;
	}
	//�X���[�v��ԂŐe�ɒǉ�
	//�Q������t���[�������w��
	template<typename Ptr>
	std::weak_ptr<Object> insertToParentSleep(Ptr* o, int framecount)
	{
		std::weak_ptr<Object> ret = insertToParent(o);
		o->sleep(framecount);
		return ret;
	}

	//-----------------------------------------------------------------------
	//�q���ɃI�u�W�F�N�g��ǉ�
	//-----------------------------------------------------------------------
	template<typename Ptr>
	std::weak_ptr<Object> insertAsChild(Ptr* p)
	{
		std::shared_ptr<Ptr> o(p);
		p->setWeakPtr(o);
		p->setParentPtr(selfPtr());
		p->hierarchyLevel_ = hierarchyLevel_ + 1;
		//AddStringToList(o->name(), o->ID());
		ins_.push_back(o);
		return o;
	}
	//�|�[�Y��ԂŎq���ɒǉ�
	template<typename Ptr>
	std::weak_ptr<Object> insertAsChildPause(Ptr* o)
	{
		std::weak_ptr<Object> ret = insertAsChild(o);
		o->pause();
		return ret;
	}
	//�X���[�v��ԂŎq���ɒǉ�
	//�Q������t���[�������w��
	template<typename Ptr>
	std::weak_ptr<Object> insertAsChildSleep(Ptr* o, int framecount)
	{
		std::weak_ptr<Object> ret = insertAsChild(o);
		o->sleep(framecount);
		return ret;
	}

	//-----------------------------------------------------------------------
	//�|�C���^�֘A
	//-----------------------------------------------------------------------
	//������weak_ptr���擾����
	std::weak_ptr<Object> selfPtr() const
	{
		return selfPtr_;
	}
	//�������g��weak_ptr��ݒ肷��i���[�g�ȊO�Ŏg���K�v�͖����j
	void setWeakPtr(const std::weak_ptr<Object>& w)
	{
		selfPtr_ = w;
	}
	//�e��weak_ptr���擾����
	std::weak_ptr<Object>  getParentPtr() const
	{
		return parentPtr_;
	}
	//���[�g�I�u�W�F�N�g��weak_ptr���擾����
	std::weak_ptr<Object> getRootObject() const
	{
		auto parent = getParentPtr();
		if (parent.expired())
			return selfPtr();
		else
			return parent.lock()->getRootObject();
	}

	//-----------------------------------------------------------------------
	//�I�u�W�F�N�g�擾�֘A
	//-----------------------------------------------------------------------
	//�S�q���^�X�N���擾
	std::vector<std::weak_ptr<Object>> getChildren() const
	{
		std::vector<std::weak_ptr<Object>> ret;
		for (auto& child : children_)
		{
			ret.push_back(child);
			auto temp = child->getChildren();
			ret.insert(ret.end(), temp.begin(), temp.end());
		}
		return ret;
	}
	//object�̖��O��findNames���ӂ��܂�Ă��邩�AfindNotNames���܂܂�Ă��Ȃ��ꍇ��true������
	//<��1>
	// object��name   "player_shot_3way"
	// findNames    = {"shot", "laser"}
	// findNotNames = {"enemy"}
	//  =>true
	//<��2>
	// object��name   "player_shot_3way"
	// findNames    = {"shot", "laser"}
	// findNotNames = {"player"}
	//  =>false
	bool findObject(
		std::weak_ptr<Object> object,
		const std::vector<std::string>& findNames,
		const std::vector<std::string>& findNotNames) const
	{
		for (auto& name : findNames)
		{
			//�T�����O���Ȃ�����������֖߂�
			if (!object.lock()->findName(name))
				continue;
			//�����Ă��Ă͂����Ȃ����O�����������猟���I��
			for (auto& name2 : findNotNames)
				if (object.lock()->findName(name2))
					return false;
			//��������
			return true;
		}
		return false;
	}
	//object�̖��O��findNames���ӂ��܂�Ă��邩�AfindNotNames���܂܂�Ă��Ȃ����̂�vector�Ŗ߂�
	//���findObject()�Q��
	std::vector<std::weak_ptr<Object>> getObjectsFromChildren(
		const std::vector<std::string>& objectNames1,
		const std::vector<std::string>& objectNotNames2 = {}) const
	{
		std::vector<std::weak_ptr<Object>> ret;
		for (auto& child : children_)
		{
			auto r = child->getObjectsFromChildren(objectNames1, objectNotNames2);
			ret.insert(ret.end(), r.begin(), r.end());
			if (findObject(child, objectNames1, objectNotNames2))
			{
				ret.push_back(child);
			}
		}
		return ret;
	}
	//object�̖��O��findNames���ӂ��܂�Ă��邩�AfindNotNames���܂܂�Ă��Ȃ����̂�vector�Ŗ߂�
	//���findObject()�Q��
	std::vector<std::weak_ptr<Object>> getObjectsFromRoot(
		const std::vector<std::string>& objectNames1,
		const std::vector<std::string>& objectNotNames2 = {}) const
	{
		std::vector<std::weak_ptr<Object>> ret;
		std::shared_ptr<Object> root = getRootObject().lock();
		for (auto& child : root->children_)
		{
			auto r = child->getObjectsFromChildren(objectNames1, objectNotNames2);
			ret.insert(ret.end(), r.begin(), r.end());
			if (findObject(child, objectNames1, objectNotNames2))
			{
				ret.push_back(child);
			}
		}
		return ret;
	}
	//�w�肵�����O��object�������̎q�����猟�����߂�
	std::weak_ptr<Object> getObjectFromChildren(
		const std::string& objectName) const
	{
		for (auto& child : children_)
		{
			if (child->name() == objectName)      return child;
			auto temp = child->getObjectFromChildren(objectName);
			if (!temp.expired()) return temp;
		}
		return std::weak_ptr<Object>();
	}
	//�w�肵�����O��object�����[�g���猟�����߂�
	std::weak_ptr<Object> getObjectFromRoot(
		const std::string& objectName) const
	{
		std::shared_ptr<Object> root = getRootObject().lock();
		for (auto& child : root->children_)
		{
			if (child->name() == objectName)      return child;
			auto temp = child->getObjectFromChildren(objectName);
			if (!temp.expired()) return temp;
		}
		return std::weak_ptr<Object>();
	}
	//�I�u�W�F�N�g�̃��j�[�NID����I�u�W�F�N�g���擾
	//�A���A�����̎q���ȉ�����T���A�e�����ɂ͌������Ȃ�
	std::weak_ptr<Object> getObjectFromChildren(int id) const
	{
		std::weak_ptr<Object> ret;
		if (ID() == id) return selfPtr();
		for (auto& child : children_)
		{
			ret = child->getObjectFromChildren(id);
			if (!ret.expired()) return ret;
		}
		return ret;
	}
	//�I�u�W�F�N�g�̃��j�[�NID����I�u�W�F�N�g���擾
	//���[�g�I�u�W�F�N�g���猟����������
	std::weak_ptr<Object> getObjectFromRoot(int id) const
	{
		auto root = getRootObject();
		return root.lock()->getObjectFromChildren(id);
	}

	//-----------------------------------------------------------------------
	//�I�u�W�F�N�g���O�֘A
	//-----------------------------------------------------------------------
	//�I�u�W�F�N�g�̖��O����v���Ă��邩�𒲂ׂ�
	bool matchingName(const std::string& name) const
	{
		return (name == name_);
	}
	//�I�u�W�F�N�g�̖��O�Ɏw��̕�����܂܂�Ă��邩�𒲂ׂ�
	bool findName(const std::string& name) const
	{
		return (name_.find(name) != std::string::npos);
	}
	//�I�u�W�F�N�g�̖��O��ύX����
	std::string changeName(const std::string& newname)
	{
		std::string oldname = name_;
		name_ = newname;
		return oldname;
	}
	//�I�u�W�F�N�g�̖��O�֒ǋL����i\0�ȍ~�Ɏw��̕������ǉ��j
	void appendName(const std::string& append)
	{
		name_ += append;
	}

	//-----------------------------------------------------------------------
	//�I�u�W�F�N�gID�֘A
	//-----------------------------------------------------------------------
	//�I�u�W�F�N�g��ID����v���Ă��邩�𒲂ׂ�
	bool matchingID(int id) const
	{
		return id_ == id;
	}
	//�I�u�W�F�N�g��ID������������
	int ID() const
	{
		return id_;
	}
	//�����I�u�W�F�N�g���ǂ����𒲂ׂ�
	bool isSame(std::weak_ptr<Object>& w) const
	{
		auto temp = weak_to_shared(w);
		if (temp == nullptr) return false;
		return (temp->ID() == ID());
	}

	//-----------------------------------------------------------------------
	//�I�u�W�F�N�g�쓮�ύX�֘A
	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	//�I�u�W�F�N�g�j���֘A
	//-----------------------------------------------------------------------
	//�I�u�W�F�N�g��j������\�������
	virtual void kill()
	{
		status_ = Status::destroy;
		for (auto& child : children_)
			child->kill();
	}
	//�w�肵�����O�̃I�u�W�F�N�g��j������\�������
	void killFromChildren(const std::string& name)
	{
		for (auto& child : children_)
		{
			if (child->name() == name)
				child->kill();
		}
	}
	//�w�肵�����O�̃I�u�W�F�N�g��j������\�������
	void killFromRoot(const std::string& name)
	{
		auto root = getRootObject().lock();
		for (auto& child : root->children_)
		{
			if (child->name() == name)
				child->kill();
		}
	}
	//object�̖��O��findNames���ӂ��܂�Ă��邩�AfindNotNames���܂܂�Ă��Ȃ����̂�j������\�������
	void killFromChildren(
		const std::vector<std::string>& objectNames1,
		const std::vector<std::string>& objectNotNames2 = {})
	{
		for (auto& child : children_)
		{
			if (findObject(child, objectNames1, objectNotNames2))
				child->kill();
		}
	}
	//object�̖��O��findNames���ӂ��܂�Ă��邩�AfindNotNames���܂܂�Ă��Ȃ����̂�j������\�������
	void killFromRoot(
		const std::vector<std::string>& objectNames1,
		const std::vector<std::string>& objectNotNames2 = {})
	{
		auto root = getRootObject().lock();
		for (auto& child : root->children_)
		{
			if (findObject(child, objectNames1, objectNotNames2))
				child->kill();
		}
	}

	//-----------------------------------------------------------------------
	//�I�u�W�F�N�g���쓮������
	//-----------------------------------------------------------------------
	virtual void run()
	{
		status_ = Status::run;
	}
	//�q�����܂߂��I�u�W�F�N�g���쓮������
	virtual void runAll()
	{
		run();
		for (auto& child : children_)
			child->runAll();
	}
	//�w�肵�����O�̃I�u�W�F�N�g���쓮������
	void runFromChildren(const std::string& name)
	{
		for (auto& child : children_)
		{
			if (child->name() == name)
				child->run();
		}
	}
	//�w�肵�����O�̃I�u�W�F�N�g���쓮������
	void runFromRoot(const std::string& name)
	{
		auto root = getRootObject().lock();
		for (auto& child : root->children_)
		{
			if (child->name() == name)
				child->run();
		}
	}
	//object�̖��O��findNames���ӂ��܂�Ă��邩�AfindNotNames���܂܂�Ă��Ȃ����̂��쓮������
	void runFromChildren(
		const std::vector<std::string>& objectNames1,
		const std::vector<std::string>& objectNotNames2 = {})
	{
		for (auto& child : children_)
		{
			if (findObject(child, objectNames1, objectNotNames2))
				child->run();
		}
	}
	//object�̖��O��findNames���ӂ��܂�Ă��邩�AfindNotNames���܂܂�Ă��Ȃ����̂��쓮������
	void runFromRoot(
		const std::vector<std::string>& objectNames1,
		const std::vector<std::string>& objectNotNames2 = {})
	{
		auto root = getRootObject().lock();
		for (auto& child : root->children_)
		{
			if (findObject(child, objectNames1, objectNotNames2))
				child->run();
		}
	}

	//-----------------------------------------------------------------------
	//�I�u�W�F�N�g���X���[�v
	//-----------------------------------------------------------------------

	virtual void sleep(int framecount)
	{
		status_ = Status::sleep;
		framecount_ = framecount;
	}
	//�q�����܂߂��X���[�v
	void sleepAll(int framecount)
	{
		sleep(framecount);
		for (auto& child : children_)
			child->sleepAll(framecount);
	}
	//�w�肵�����O�̃I�u�W�F�N�g���X���[�v������
	void pauseFromChildren(const std::string& name, int framecount)
	{
		for (auto& child : children_)
		{
			if (child->name() == name)
				child->sleep(framecount);
		}
	}
	//�w�肵�����O�̃I�u�W�F�N�g���X���[�v������
	void pauseFromRoot(const std::string& name, int framecount)
	{
		auto root = getRootObject().lock();
		for (auto& child : root->children_)
		{
			if (child->name() == name)
				child->sleep(framecount);
		}
	}
	//object�̖��O��findNames���ӂ��܂�Ă��邩�AfindNotNames���܂܂�Ă��Ȃ����̂��X���[�v������
	void pauseFromChildren(
		const std::vector<std::string>& objectNames1,
		const std::vector<std::string>& objectNotNames2,
		int framecount)
	{
		for (auto& child : children_)
		{
			if (findObject(child, objectNames1, objectNotNames2))
				child->sleep(framecount);
		}
	}
	//object�̖��O��findNames���ӂ��܂�Ă��邩�AfindNotNames���܂܂�Ă��Ȃ����̂��X���[�v������
	void pauseFromRoot(
		const std::vector<std::string>& objectNames1,
		const std::vector<std::string>& objectNotNames2,
		int framecount)
	{
		auto root = getRootObject().lock();
		for (auto& child : root->children_)
		{
			if (findObject(child, objectNames1, objectNotNames2))
				child->sleep(framecount);
		}
	}

	//-----------------------------------------------------------------------
	//�I�u�W�F�N�g���~������
	//-----------------------------------------------------------------------
	virtual void pause()
	{
		status_ = Status::pause;
	}
	//�q�����܂߂���~
	void pauseAll()
	{
		pause();
		for (auto& child : children_)
			child->pauseAll();
	}
	//�w�肵�����O�̃I�u�W�F�N�g���~������
	void pauseFromChildren(const std::string& name)
	{
		for (auto& child : children_)
		{
			if (child->name() == name)
				child->pause();
		}
	}
	//�w�肵�����O�̃I�u�W�F�N�g���~������
	void pauseFromRoot(const std::string& name)
	{
		auto root = getRootObject().lock();
		for (auto& child : root->children_)
		{
			if (child->name() == name)
				child->pause();
		}
	}
	//object�̖��O��findNames���ӂ��܂�Ă��邩�AfindNotNames���܂܂�Ă��Ȃ����̂��~������
	void pauseFromChildren(
		const std::vector<std::string>& objectNames1,
		const std::vector<std::string>& objectNotNames2 = {})
	{
		for (auto& child : children_)
		{
			if (findObject(child, objectNames1, objectNotNames2))
				child->pause();
		}
	}
	//object�̖��O��findNames���ӂ��܂�Ă��邩�AfindNotNames���܂܂�Ă��Ȃ����̂��~������
	void pauseFromRoot(
		const std::vector<std::string>& objectNames1,
		const std::vector<std::string>& objectNotNames2 = {})
	{
		auto root = getRootObject().lock();
		for (auto& child : root->children_)
		{
			if (findObject(child, objectNames1, objectNotNames2))
				child->pause();
		}
	}
	//���W���[��
	virtual void resume()
	{
		status_ = Status::run;
	}

	//-----------------------------------------------------------------------
	//�A�N�Z�T
	//-----------------------------------------------------------------------
	const std::string& name() const { return name_; }
	bool isDestroy()  const { return (status_ == Status::destroy); }
	bool isDead()  const { return (status_ == Status::dead); }
	bool isRunning()  const { return (status_ == Status::run); }
	bool isSleeping() const { return (status_ == Status::sleep); }
	bool isPause()    const { return (status_ == Status::pause); }
	Status status() const { return status_; }
	int  priority() const { return priority_; }
	void changePriority(int priority) { priority_ = priority; }


	//-----------------------------------------------------------------------
	//��r�p���q�֐�
	//-----------------------------------------------------------------------
	static bool greaterPriority(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b)
	{
		return a->priority() > b->priority();
	}
	static bool lessPriority(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b)
	{
		return a->priority() < b->priority();
	}

	//-----------------------------------------------------------------------
	//���b�Z�[�W���M�i�������j
	//-----------------------------------------------------------------------
	virtual int receiveMsg(std::weak_ptr<Object>& sender, const std::string& msg) { return 0; }
	virtual int postMsg(std::weak_ptr<Object>& receiver, const std::string& msg) { return receiver.lock()->receiveMsg(selfPtr(), msg); }

	virtual int receiveMsg(Object* sender, const std::string& msg) { return 0; }
	virtual int postMsg(Object* receiver, const std::string& msg) { return receiver->receiveMsg(this, msg); }

	//-----------------------------------------------------------------------
	//render�֘A
	//-----------------------------------------------------------------------
	//���[�g�ȊO�ŌĂ΂Ȃ��ł�������
	virtual void renderWithChildren()
	{
		render();
		//TODO: Z���y�уA���t�@���l�������`�揇���\�z���邱��
		renderSelect();
	}
	//override���Ċe�X�e�[�^�X��render���L�q����
	virtual void render() {};     //�ʏ�`�揈��
	virtual void renderPause() { render(); } //�|�[�Y���̏���
	virtual void renderSleep() { render(); } //�X���[�v���̏���
	virtual void renderDestroy() {} //�폜�\�񒆂̏���

	//-----------------------------------------------------------------------
	//update�֘A
	//-----------------------------------------------------------------------
	//���[�g�ȊO�ŌĂ΂Ȃ��ł�������
	void updateWithChildren()
	{
		update();
		updateChildObjects();
	}
	//override���Ċe�X�e�[�^�X��update���L�q����
	virtual void update() {}     //�ʏ폈��
	virtual void updatePause() {} //�|�[�Y���̏���
	virtual void updateSleep() {} //�X���[�v���̏���
	virtual void updateDestroy() {} //�폜�\�񒆂̏���

	//-----------------------------------------------------------------------
	//�����蔻��p�i�Q�[��PG���ޗp�Ɂj
	//-----------------------------------------------------------------------
	//���ꔻ��ɍU����H�����
	virtual void defenseHit(std::weak_ptr<Object>&) {}
	//�U������ɂ��U����^����
	virtual void offenseHit(std::weak_ptr<Object>&) {}

	//-----------------------------------------------------------------------
	//�����蔻��p�i�Q�[��PG���ޗp�Ɂj
	//-----------------------------------------------------------------------
	//�R���X�g���N�^�ł͐e�q�֌W���\�z�ł��Ȃ��d�l�Ȃ̂ŁA
	//�������Ɏq����o�^�������ꍇ��init()�ōs��
	virtual void init() {}

	//0307�ǉ�
	//�����̎q���̐��i���ȍ~�͊܂܂Ȃ��j��Ԃ�
	int childrenCount() const {
		return (int)children_.size();
	}

private:
	//�e�q�֌W�\�z�p
	std::weak_ptr<Object> selfPtr_;   //�������g��weak_ptr
	std::weak_ptr<Object> parentPtr_; //�e��weak_ptr
	//�q���^�X�N�o�^�ł���悤�ɂ���
	std::vector<std::shared_ptr<Object>> children_; //�q���I�u�W�F�N�g
	std::vector<std::shared_ptr<Object>> ins_;      //�ǉ�����I�u�W�F�N�g

	static int uid_;     //���j�[�N��ID�A�I�u�W�F�N�g�𐶐�����ƃC���N�������g�����
	int id_;             //�I�u�W�F�N�gID�A����ID�ŃI�u�W�F�N�g����肵���茟���������邱�Ƃ��ł���
	int priority_;       //�D�揇�ʁA���ݖ��g�p
	std::string name_;   //�I�u�W�F�N�g�̖��O�A���̖��O�Ō����������邱�Ƃ��ł���
	int hierarchyLevel_; //�ǂ̊K�w�ɂ��邩�B���[�g��1�A�q���ɂȂ�ɂ�+1���Ă���
	int framecount_;     //�Q������t���[�����A�ʏ�쓮����0
	Status status_;      //�쓮�X�e�[�^�X

	//�e�q�֌W�\�z�p�F�e��weak_ptr��ݒ肷��
	void setParentPtr(const std::weak_ptr<Object>& w)
	{
		parentPtr_ = w;
	}
	//�������Ƀ��j�[�NID��ݒ肷��
	void initID()
	{
		++uid_;
		id_ = uid_;
		//      std::ofstream f("a.txt", std::ofstream::app);
		//      f << name_ << std::endl;
	}
	//sleep����run�ւ̃`�F�b�N�p
	void awake()
	{
		if (--framecount_ < 0)
			resume();
	}

	//-----------------------------------------------------------------------
	//update�֘A
	//�P�D���[�g�̂�updateWithChildren()���ĂсA�I�u�W�F�N�g�̐e�q�֌W�̋쓮���͂��߂�
	//�Q�DupdateWithChildren()��updateChildObjects()���Ăюq���I�u�W�F�N�g�̋쓮���s��
	//    updateChildObjects()���ŃI�u�W�F�N�g�̍폜�A�ǉ����s����
	//    ���̍�updateSelect()���쓮�X�e�[�^�X�ɂ���Ċe�X��update()���Ăяo��
	//�R�D�v���O���}�͊e�I�u�W�F�N�g���Ƃ�update()���쐬���Ȃ���΂Ȃ�Ȃ�
	//-----------------------------------------------------------------------
	void updateWithChildrenNormal()
	{
		update();
		updateChildObjects();
	}
	void updatePauseWithChildren()
	{
		updatePause();
		updateChildObjects();
	}
	void updateSleepWithChildren()
	{
		updateSleep();
		awake();
		updateChildObjects();
	}
	void updateDestroyWithChildren()
	{
		status_ = Status::dead;
		updateDestroy();
		updateChildObjects();
	}
	void updateSelect()
	{
		switch (status())
		{
		case Status::run:
			updateWithChildrenNormal();
			break;
		case Status::pause:
			updatePauseWithChildren();
			break;
		case Status::sleep:
			updateSleepWithChildren();
			break;
		case Status::destroy:
			updateDestroyWithChildren();
			break;
		}
	}
	void updateChildObjects()
	{
		for (auto& child : children_)
		{
			child->updateSelect();
		}

		//�I�u�W�F�N�g�̏����y�ђǉ�
		children_.erase(
			std::remove_if(children_.begin(), children_.end(),
				std::mem_fn(&Object::isDead)),
			children_.end()
		);
		insert();
	}
	//�v�[������Ă���I�u�W�F�N�g��ǉ�����
	void insert()
	{
		if (!ins_.empty())
		{
			children_.insert(children_.end(), ins_.begin(), ins_.end());
			for (auto& ins : ins_)
				ins->init();
		}
		ins_.clear();
	}

	//-----------------------------------------------------------------------
	//render�֘A
	//�P�D���[�g�̂�renderWithChildren()���ĂсA�I�u�W�F�N�g�̐e�q�֌W�̕`����͂��߂�
	//    �A���t�@�u�����h���ŕs����o��ꍇ�́A�ʓr�`�揇���\�z���Ȃ���΂Ȃ�Ȃ�
	//�Q�D�v���O���}�͊e�I�u�W�F�N�g���Ƃ�render()���쐬���Ȃ���΂Ȃ�Ȃ�
	//-----------------------------------------------------------------------
	void renderWithChildrenNormal()
	{
		render();
		renderChildObjects();
	}
	void renderPauseWithChildren()
	{
		renderPause();
		renderChildObjects();
	}
	void renderSleepWithChildren()
	{
		renderSleep();
		renderChildObjects();
	}
	void renderDestroyWithChildren()
	{
		renderDestroy();
		renderChildObjects();
	}
	void renderSelect()
	{
		switch (status())
		{
		case Status::run:
			renderWithChildrenNormal();
			break;
		case Status::pause:
			renderPauseWithChildren();
			break;
		case Status::sleep:
			renderSleepWithChildren();
			break;
		case Status::destroy:
			renderDestroyWithChildren();
			break;
		}
	}
	void renderChildObjects()
	{
		for (auto& child : children_)
		{
			child->renderSelect();
		}
	}
};
