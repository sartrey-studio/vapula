#include "tcm_cdev.h"
#include "NodeClass.h"
#include "NodeJudge.h"
#include "DataSource.h"
#include <fstream>
#include <vector>

using std::vector;

//��ȡ�ڵ�
NodeBase* GetNodeById(vector<NodeBase*> nodes,int id);

//����Lua����ֵ
void LuaSetData(LPVOID luastate, PCSTR key, double value);

//����������
NodeBase* BuildDeciTree(PCWSTR file,vector<NodeBase*>* tree);

//��������Դ
DataSource* LoadDataSource(PCWSTR file);

//Ԥ���������
LPVOID PreCompile(vector<NodeBase*>* tree,DataSource* ds);

//ִ�о�����
void ExecDeciTree(LPVOID luastate, NodeBase* treeroot,DataSource* dsrc,tcm::Context* ctx);

//��������Ϣ
void OutputHeader(vector<NodeBase*>* tree, DataSource* ds);

//����
void Clear(vector<NodeBase*>* tree);

//ԭ�ӷ���
BYTE Classify(NodeBase* treeroot,LPVOID luastate);

//��������
void RecombineData(PDataSet* dsrc,LPVOID luastate,int total,int index);