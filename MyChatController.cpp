#include <sstream>
#include "MyChat.h"
#define ENTER 13
#define BACKSPACE 8

using namespace MyChat;
using namespace std;

ChatController::ChatController() {
	memset(this->msgBuffer, 0, sizeof(msgBuffer));
	this->msgBufferIndex = 0;
	this->recvFlag = 0;
	chatView.paintChatDisplay(msgList);
}

void ChatController::run(string user) {
	while (true) {
		if (recvFlag == 1) { // 서버에서 메시지가 왔을 때,
			repaintWhenRecvFromServer();
		}
		if (kbhit()) { // 키보드가 입력됐을 때
			char key = getch(); // 키값을 가져오고

			if (key == ENTER) { // 엔터라면
				sendToServer(user);
			}
			else if (key == BACKSPACE) {

			}
			else {
				msgBuffer[msgBufferIndex++] = key;
				cout << key;
			}
		}
	}
}

void ChatController::repaintWhenRecvFromServer() {
	// 채팅 메시지 저장
	msgList.push_back("서버에서 메시지가 옴..");

	// 채팅창 다시 그리기
	chatView.paintChatDisplay(msgList);

	// 입력중이던 채팅 메시지를 다시 그려줌
	for (int i = 0; i < msgBufferIndex; i++) {
		cout << msgBuffer[i];
	}

	// 입력 커서를 index 위치로 바꿈
	chatView.moveToChatInputPosX(msgBufferIndex);

	// 평상시 상태로 바꿈
	recvFlag = 0;
}

string ChatController::convertChatDataToString(string user, const char* msg) {
	string rsMsg;
	rsMsg = rsMsg.append(user);
	rsMsg = rsMsg.append(":");
	rsMsg = rsMsg.append(msg);
	rsMsg = rsMsg.append("\n");

	return msg;
}

ChatData ChatController::convertStringToChatData(string msg) {
	ChatData chatData;

	vector<string> answer;
	stringstream ss(msg);
	string temp;

	while (getline(ss, temp, ':')) {
		answer.push_back(temp);
	}
	
	chatData.userId = answer[0];
	chatData.msg = answer[1].c_str();

	return chatData;
}

int ChatController::joinServer(string ip, int port) {
	if (chatSocket == NULL) {
		chatSocket = new MySocket::Socket(ip.c_str(), port);
		return 0;
	}
	else {
		return -1;
	}
}

void ChatController::sendToServer(string user) {
	// 메시지 보내기
	memset(msgBuffer, 0, sizeof(msgBuffer)); // msgBuffer의 내용 비운다.
	string sendMsg = convertChatDataToString(user, msgBuffer);

	// 메시지를 보냈으므로 채팅창 다시 그리고
	chatSocket->send_data(sendMsg.c_str());

	chatView.paintChatDisplay(msgList);
	// 메시지를 보냈으므로 메시지 버퍼 index초기화, 커서의 위치 초기화
	msgBufferIndex = 0;
	chatView.instantiateChatInputPos();

}

void ChatController::setRecvFlag(int recvFlag) {
	this->recvFlag = recvFlag;
}
