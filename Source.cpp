#include "MySocket.h"
#include "MyChat.h"
#include <sstream>
#include <map>
#pragma comment(lib, "ws2_32") // 윈도우 소켓 프로그래밍 기능 제공 라이브러리
#define SIZE 5
#define ID_SIZE 10

using namespace std;
using namespace MySocket;
using namespace MyChat;

//string tmpSendMsg;
//int tmpSaveFlag = false;
//int isFirstMsg = true;
//char sendBuff[100];
//char sendBuffSize = 0;

//vector<ChatData*> chatDataList = vector<ChatData*>();

//void printChatMsg() {
//	//system("cls");
//	cout << "================ 채팅 v1 ================" << endl;
//	for (ChatData* chatData : chatDataList) {
//		cout << chatData->userId << " : ";
//		cout << chatData->msg << endl;
//	}
//	cout << "=========================================" << endl;
//	//printSendMsg();
//	tmpSaveFlag = false;
//}
//
//vector<string> split(string input, char delimiter) {
//	vector<string> answer;
//	stringstream ss(input);
//	string temp;
//
//	while (getline(ss, temp, delimiter)) {
//		answer.push_back(temp);
//	}
//
//	return answer;
//}
//
//ChatData* mapToChatData(map<string, string> chatMap) {
//	ChatData* chatData = new ChatData();
//	chatData->userId = chatMap["userId"];
//	chatData->msg = chatMap["msg"];
//
//	return chatData;
//}
//
//const char* toChatDataBytes(ChatData* chatData) {
//	string data = "";
//	data = data.append("userId:");
//	data = data.append(chatData->userId);
//	data = data.append("msg:");
//	data = data.append(chatData->msg);
//
//	return data.c_str();
//}
//
//ChatData* toChatDataObject(string msg) {
//
//	vector<string> msgBits= split(msg, ',');
//	map<string, string> chatMap;
//	for (string msgBit : msgBits) {
//		vector<string> keyAndValue = split(msgBit, ':');
//		chatMap[keyAndValue[0]] = keyAndValue[1];
//	}
//	ChatData* chatData = mapToChatData(chatMap);
//	cout << "chatData -> userId : " << chatData->userId << endl;
//	cout << "chatData -> msg : " << chatData->msg << endl;
//	return chatData;
//}
//
//void recvBack() {
//	char recvMsg[100] = {0};
//	while (true) {
//		strcpy(recvMsg, skt->recv_data());
//		cout << "recvMsg : " << recvMsg << endl;
//		if (!isFirstMsg) {
//			ChatData* chatData = toChatDataObject(string(recvMsg));
//			chatDataList.push_back(chatData);
//		}
//		tmpSaveFlag = true;
//		printChatMsg();
//	}
//}

string loginedUser;
ChatController* cc;
ChatView* cv;

void test() {
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(5000));
		cc->setRecvFlag(1);
	}
}

//=======================================================
int main() {

	cout << "사용할 이름을 입력해주세요 : ";
	cin >> loginedUser;

	cc = new ChatController();
	cv = new ChatView();
	thread t1(test);
	
	cc->run(loginedUser);
	t1.join();

	//skt = new Socket(9999, "127.0.0.1");

	//thread t1(recvBack);
	//t1.join();

	return 0;
}
