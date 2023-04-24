#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
using namespace std;

//khoi tao ban co
int** init_board()
{
	int** t = new int* [5];
	for (int i = 0; i < 5; i++)
	{
		t[i] = new int[5];
		if (i == 0)
		{
			for (int j = 0; j < 5; j++)
				t[i][j] = 1;
		}
		if (i == 4)
		{
			for (int j = 0; j < 5; j++)
				t[i][j] = -1;
		}
	}
	t[1][0] = 1; t[1][4] = 1; t[2][0] = 1;
	t[2][4] = -1; t[3][0] = -1; t[3][4] = -1;
	return t;
}

//copy ban co hien tai
int** copy_board(int** board)
{
	int** n_b = new int* [5];
	for (int i = 0; i < 5; i++)
	{
		n_b[i] = new int[5];
		for (int j = 0; j < 5; j++)
		{
			n_b[i][j] = board[i][j];
		}
	}
	return n_b;
}

//in ban co
void print_board(int** board)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (board[4 - i][j] == 1)
				cout << "X ";
			else if (board[4 - i][j] == -1)
				cout << "D ";
			else
				cout << "- ";
		}
		cout << endl;
	}
}

struct Position
{
	int x; int y; //x= row, y = column
	Position() { x = y = 0; }
	Position(int a, int b)
	{
		x = a; y = b;
	}
};

struct Move
{
	Position pos_start, pos_end;
	Move(Position s, Position e)
	{
		pos_start = s; pos_end = e;
	}
};



//-------------------------------------------------------------------------------

//xoa ban co
void clearBoard(int** &board) {
	if (board == nullptr) {
		return;
	}

	for (int row = 0; row < 5; row++) {
		delete[] board[row];
	}
	delete[] board;
	
	return;
}


//in ban co the hien nuoc di cua player
void print_board_move(int** preBoard, Move m)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if ((4 - i) == m.pos_start.x && j == m.pos_start.y) {
				cout << "1 ";
			}
			else if ((4 - i) == m.pos_end.x && j == m.pos_end.y) {
				cout << "2 ";
			}
			else {
				if (preBoard[4 - i][j] == 1)
					cout << "X ";
				else if (preBoard[4 - i][j] == -1)
					cout << "D ";
				else
					cout << "- ";
			}
		}
		cout << endl;
	}
}


//tra ve danh sach vi tri cac quan co lan can
vector<Position>** lanCan() {
	vector<Position>** tp = new vector<Position>*[5];
	for (int i = 0; i < 5; i++) {
		tp[i] = new vector<Position>[5];
	}

	Position** tp2 = new Position * [5];
	for (int row = 0; row < 5; row++) {
		tp2[row] = new Position[5];
		for (int col = 0; col < 5; col++) {
			tp2[row][col].x = row;
			tp2[row][col].y = col;
		}
	}

	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 5; col++) {
			if (row == 0) {
				if (col > 0) {
					tp[row][col].push_back(tp2[row][col - 1]);
				}
				if (col < 4) {
					tp[row][col].push_back(tp2[row][col + 1]);
				}
				if (col == 2 || col == 4) {
					tp[row][col].push_back(tp2[row + 1][col - 1]);
				}

				tp[row][col].push_back(tp2[row + 1][col]);

				if (col == 0 || col == 2) {
					tp[row][col].push_back(tp2[row + 1][col + 1]);
				}
			}
			else if (row > 0 && row < 4) {
				if ((row == 1 && col == 1) || (row == 1 && col == 3) || (row == 2 && col == 2)
					|| (row == 2 && col == 4) || (row == 3 && col == 1) || (row == 3 && col == 3)) {

					tp[row][col].push_back(tp2[row - 1][col - 1]);
				}

				tp[row][col].push_back(tp2[row - 1][col]);

				if ((row == 1 && col == 1) || (row == 1 && col == 3) || (row == 2 && col == 0)
					|| (row == 2 && col == 2) || (row == 3 && col == 1) || (row == 3 && col == 3)) {

					tp[row][col].push_back(tp2[row - 1][col + 1]);
				}

				if (col > 0) {
					tp[row][col].push_back(tp2[row][col - 1]);
				}

				if (col < 4) {
					tp[row][col].push_back(tp2[row][col + 1]);
				}

				if ((row == 1 && col == 1) || (row == 1 && col == 3) || (row == 2 && col == 2)
					|| (row == 2 && col == 4) || (row == 3 && col == 1) || (row == 3 && col == 3)) {

					tp[row][col].push_back(tp2[row + 1][col - 1]);
				}

				tp[row][col].push_back(tp2[row + 1][col]);

				if ((row == 1 && col == 1) || (row == 1 && col == 3) || (row == 2 && col == 0)
					|| (row == 2 && col == 2) || (row == 3 && col == 1) || (row == 3 && col == 3)) {

					tp[row][col].push_back(tp2[row + 1][col + 1]);
				}
			}
			else {
				if (col == 2 || col == 4) {
					tp[row][col].push_back(tp2[row - 1][col - 1]);
				}

				tp[row][col].push_back(tp2[row - 1][col]);

				if (col == 0 || col == 2) {
					tp[row][col].push_back(tp2[row - 1][col + 1]);
				}

				if (col > 0) {
					tp[row][col].push_back(tp2[row][col - 1]);
				}

				if (col < 4) {
					tp[row][col].push_back(tp2[row][col + 1]);
				}
			}
		}
	}
	return tp;
}

//Bien toan cuc, danh sach cac quan lan can
vector<Position>** dsLanCan = lanCan();

//tao ban co ghe tham
bool** init_boolBoard() {
	bool** boolBoard = new bool* [5];
	for (int i = 0; i < 5; i++) {
		boolBoard[i] = new bool[5];
		for (int j = 0; j < 5; j++) {
			boolBoard[i][j] = false;
		}
	}
	return boolBoard;
}

//kiem tra nuoc di
bool checkMove(int** board, Move m, int player) {
	bool result = false;
	int value = board[m.pos_start.x][m.pos_start.y];
	if (value == player) {
		int mEndX = m.pos_end.x;
		int mEndY = m.pos_end.y;
		Position tp(mEndX, mEndY);
		vector<Position> lanCan = dsLanCan[m.pos_start.x][m.pos_start.y];
		for (unsigned int i = 0; i < lanCan.size(); i++) {
			if (mEndX == lanCan[i].x && mEndY == lanCan[i].y) {
				result = true;
			}
		}
	}
	return result;
}

//tra ve danh sach vi tri cac quan cua doi thu bi GANH
vector<Position> ganh(int** board, Move m, int player) {
	vector<Position> result;
	if (checkMove(board, m, player)) {
		int t = player * (-1);
		Position k;

		//x=row, y= col
		int peRowY = m.pos_end.x;	//row
		int peColX = m.pos_end.y;	//col

		if (peRowY == 0 || peRowY == 4) {
			if (peColX > 0 && peColX < 4) {
				/*duong ngang ---
				*/
				if (board[peRowY][peColX - 1] == t
					&& board[peRowY][peColX + 1] == t) {

					k.x = peRowY;
					k.y = peColX - 1;
					result.push_back(k);

					k.x = peRowY;
					k.y = peColX + 1;
					result.push_back(k);
				}
			}
		}
		else if (peColX == 0 || peColX == 4) {
			if (peRowY > 0 && peRowY < 4) {
				/*duong doc |
				*/
				if (board[peRowY - 1][peColX] == t
					&& board[peRowY + 1][peColX] == t) {

					k.x = peRowY - 1;
					k.y = peColX;
					result.push_back(k);

					k.x = peRowY + 1;
					k.y = peColX;
					result.push_back(k);
				}
			}
		}
		else {
			if ((peColX == 1 && peRowY == 1) || (peColX == 1 && peRowY == 3)
				|| (peColX == 2 && peRowY == 2) || (peColX == 3 && peRowY == 1)
				|| (peColX == 3 && peRowY == 3)) {

				/*duong cheo \
				*/
				if (board[peRowY - 1][peColX - 1] == t
					&& board[peRowY + 1][peColX + 1] == t) {

					k.x = peRowY - 1;
					k.y = peColX - 1;
					result.push_back(k);

					k.x = peRowY + 1;
					k.y = peColX + 1;
					result.push_back(k);
				}

				/*duong cheo /
				*/
				if (board[peRowY + 1][peColX - 1] == t
					&& board[peRowY - 1][peColX + 1] == t) {

					k.x = peRowY + 1;
					k.y = peColX - 1;
					result.push_back(k);

					k.x = peRowY - 1;
					k.y = peColX + 1;
					result.push_back(k);
				}
			}

			/*duong ngang ---
			*/
			if (board[peRowY][peColX - 1] == t
				&& board[peRowY][peColX + 1] == t) {

				k.x = peRowY;
				k.y = peColX - 1;
				result.push_back(k);

				k.x = peRowY;
				k.y = peColX + 1;
				result.push_back(k);
			}

			/*duong doc |
			*/
			if (board[peRowY - 1][peColX] == t
				&& board[peRowY + 1][peColX] == t) {

				k.x = peRowY - 1;
				k.y = peColX;
				result.push_back(k);

				k.x = peRowY + 1;
				k.y = peColX;
				result.push_back(k);
			}
		}
	}
	return result;
}

vector<Position> timHangXomXungQuanh(int** board, Position k, int player) {
	vector<Position> result;
	vector<Position> quanXungQuanh = dsLanCan[k.x][k.y];
	for (unsigned int i = 0; i < quanXungQuanh.size(); i++) {
		if (board[quanXungQuanh[i].x][quanXungQuanh[i].y] == player) {
			result.push_back(quanXungQuanh[i]);
		}
	}
	return result;
}

vector<Position> timDoiThuXungQuanh(int** board, Position k, int player) {
	int doiThu = player * (-1);
	vector<Position> result;
	vector<Position> quanXungQuanh = dsLanCan[k.x][k.y];
	for (unsigned int i = 0; i < quanXungQuanh.size(); i++) {
		if (board[quanXungQuanh[i].x][quanXungQuanh[i].y] == doiThu) {
			result.push_back(quanXungQuanh[i]);
		}
	}
	return result;
}

bool biVay(int** board, Position k) {
	//vector<Position> quanXungQuanh = dsLanCan[k.x][k.y];
	unsigned int soDuongDiBiVay = 0;
	vector<Position> quanXungQuanh = dsLanCan[k.x][k.y];
	for (unsigned int i = 0; i < quanXungQuanh.size(); i++) {
		if (board[quanXungQuanh[i].x][quanXungQuanh[i].y] == 1
			|| board[quanXungQuanh[i].x][quanXungQuanh[i].y] == -1) {
			soDuongDiBiVay++;
		}
	}
	if (soDuongDiBiVay == quanXungQuanh.size()) {
		return true;
	}
	return false;
}

void timHangXomRec(int** board, Position m, int player, bool**& boolBoard, vector<Position>& result) {
	vector<Position> quanXungQuanh = dsLanCan[m.x][m.y];
	boolBoard[m.x][m.y] = true;

	for (unsigned int i = 0; i < quanXungQuanh.size(); i++) {
		Position q(quanXungQuanh[i].x, quanXungQuanh[i].y);
		if (board[q.x][q.y] == player) {
			if (boolBoard[q.x][q.y] == false) {
				result.push_back(q);
				timHangXomRec(board, q, player, boolBoard, result);
			}
		}
	}
	return;
}

vector<Position> timHangXom(int** board, Position m, int player) {
	vector<Position> result;
	bool** boolBoard = init_boolBoard();
	timHangXomRec(board, m, player, boolBoard, result);
	return result;

}

vector<Position> vay(int** board, Move m, int player) {
	vector<Position> resultVay;

	if (checkMove(board, m, player)) {
		vector<Position> resultGanh;
		vector<Position> quanTa;
		vector<Position> viTriDaXetVay;
		bool daXetViTriNay = false;

		int** tmpBoard = copy_board(board);
		//kiem tra GANH
		resultGanh = ganh(tmpBoard, m, player);
		if (resultGanh.size()) {
			for (unsigned int i = 0; i < resultGanh.size(); i++) {
				tmpBoard[resultGanh[i].x][resultGanh[i].y] = player;
				quanTa.push_back(resultGanh[i]);
			}
		}
		tmpBoard[m.pos_start.x][m.pos_start.y] = 0;
		tmpBoard[m.pos_end.x][m.pos_end.y] = player;
		quanTa.push_back(Position(m.pos_end.x, m.pos_end.y));


		for (unsigned int h = 0; h < quanTa.size(); h++) {
			vector<Position> doiThu = timDoiThuXungQuanh(tmpBoard, quanTa[h], player);
			if (doiThu.size() != 0) {
				for (unsigned int i = 0; i < doiThu.size(); i++) {
					if (viTriDaXetVay.size() == 0) {
						viTriDaXetVay.push_back(doiThu[i]);
					}
					else {
						for (unsigned int j = 0; j < viTriDaXetVay.size(); j++) {
							if ((viTriDaXetVay[j].x == doiThu[i].x) && (viTriDaXetVay[j].y == doiThu[i].y)) {
								daXetViTriNay = true;
								break;
							}
						}
						viTriDaXetVay.push_back(doiThu[i]);
					}
					if (daXetViTriNay) {
						daXetViTriNay = false;
						continue;
					}
					if (biVay(tmpBoard, Position(doiThu[i].x, doiThu[i].y))) {
						vector<Position> hangXom = timHangXom(tmpBoard, doiThu[i], player * (-1));
						if (hangXom.size() != 0) {
							unsigned int hangXomBiVay = 0;
							for (unsigned int j = 0; j < hangXom.size(); j++) {
								if (biVay(tmpBoard, Position(hangXom[j].x, hangXom[j].y))) {
									hangXomBiVay++;
								}
								else {
									break;
								}
							}
							if (hangXomBiVay == hangXom.size()) {
								resultVay.push_back(Position(doiThu[i].x, doiThu[i].y));
								for (unsigned int j = 0; j < hangXom.size(); j++) {
									Position newVay(hangXom[j].x, hangXom[j].y);
									resultVay.push_back(newVay);
									viTriDaXetVay.push_back(newVay);
								}
							}
							else {
								continue;
							}
						}
						else {
							resultVay.push_back(Position(doiThu[i].x, doiThu[i].y));
						}
					}
				}
			}
		}

		//if (resultVay.size() != 0) {
		//	resultGanh = ganh(tmpBoard, m, player);
		//	if (resultGanh.size() != 0) {
		//		while (!resultVay.empty()) {
		//			stack.push_back(resultVay.back());
		//			resultVay.pop_back();
		//			for (unsigned int u = 0; u < resultGanh.size(); u++) {
		//				if ((stack.back().x == resultGanh[u].x) && (stack.back().y == resultGanh[u].y)) {
		//					stack.pop_back();
		//				}
		//			}
		//		}
		//	}
		//	else {
		//		while (!resultVay.empty()) {
		//			stack.push_back(resultVay.back());
		//			resultVay.pop_back();
		//		}
		//	}
		//}

		//xoa ban co
		clearBoard(tmpBoard);
	}
	return resultVay;
}

//tra ve danh sach cac nuoc PHAI di theo luat BAY
vector<Move> bay_or_mo(int** current_board, int** previous_board, int player) {

	vector<Move> result;
	Position preStart;
	Position preEnd;
	vector<Position> viTriQuanTaDiVaoBay;
	int enemy = player * (-1);


	preStart.x = -7;
	preStart.y = -7;
	preEnd.x = -7;
	preEnd.y = -7;

	
	if (previous_board == nullptr) {	//neu tran dau vua moi bat dau thi chua co bay nao ca
		return result;
	}
	else {
		int** tmpCurrBoard = copy_board(current_board);
		int** tmpPreBoard = copy_board(previous_board);

		//tim nuoc di ma doi thu vua di truoc do
		for (int row = 0; row < 5; row++) {
			for (int col = 0; col < 5; col++) {
				int preValue = tmpPreBoard[row][col];
				int currValue = tmpCurrBoard[row][col];
				if (preValue != 1 && preValue != -1 && currValue == enemy) {
					//diem ket thuc
					preEnd.x = row;
					preEnd.y = col;
				}
				if (preValue == enemy && currValue != 1 && currValue != -1) {
					//diem bat dau
					preStart.x = row;
					preStart.y = col;

				}
				
			}
		}
		Move preMove(preStart, preEnd);
		//kiem tra nuoc di doi thu vua di co ganh/vay quan minh khong
			//neu khong, thi kha nang do la BAY
		//v1
		//vector<Position> preGanh = ganh(tmpPreBoard, preMove, enemy);
		//
		
		//v2
		int soQuanBiGanhHoacVay = (int)(ganh(tmpPreBoard, preMove, enemy).size() + vay(tmpPreBoard, preMove, enemy).size());
		//

		//v1
		//if (preGanh.size() == 0) {
		
		//v2
		if(soQuanBiGanhHoacVay == 0){
			//tim vi tri quan co cua ta co the di vao vi tri quan doi thu vua roi khoi va GANH doi thu
				/*neu co, thi xet nuoc di tiep theo cua doi thu, neu doi thu di vao vi tri quan ta vua roi khoi
				va GANH quan ta, thi do la vi tri BAY, bat buoc phai di vao, co bao nhieu quan ta vao BAY duoc
				thi co bay nhieu nuoc di BAY
				*/
			vector<Position> preLanCan = dsLanCan[preStart.x][preStart.y];
			for (unsigned int i = 0; i < preLanCan.size(); i++) {
				int quanGanBay = tmpCurrBoard[preLanCan[i].x][preLanCan[i].y];
				if (quanGanBay == player) {
					viTriQuanTaDiVaoBay.push_back(Position(preLanCan[i].x, preLanCan[i].y));
				}
			}
			//for (unsigned int i = 0; i < viTriQuanTaDiVaoBay.size(); i++) {
			//	Move t(viTriQuanTaDiVaoBay[i], preStart);
			//	result.push_back(t);
			//}

			for (unsigned int i = 0; i < viTriQuanTaDiVaoBay.size(); i++) {
				Move t(viTriQuanTaDiVaoBay[i], preStart);
				vector<Position> rtGanh = ganh(tmpCurrBoard, t, player);
				if (rtGanh.size() != 0) {
					int** tmpBoard22 = copy_board(tmpCurrBoard);
					tmpBoard22[t.pos_end.x][t.pos_end.y] = player;
					tmpBoard22[t.pos_start.x][t.pos_start.y] = 0;

					for (unsigned int k = 0; k < rtGanh.size(); k++) {
						tmpBoard22[rtGanh[k].x][rtGanh[k].y] = player;
					}

					vector<Position> dsLCt = dsLanCan[t.pos_start.x][t.pos_start.y];
					for (unsigned int w = 0; w < dsLCt.size(); w++) {
						if (tmpBoard22[dsLCt[w].x][dsLCt[w].y] == enemy) {
							if (ganh(tmpBoard22, Move(Position(dsLCt[w].x, dsLCt[w].y), Position(t.pos_start.x, t.pos_start.y)), enemy).size()) {
								result.push_back(t);
							}
						}
					}

					//xoa ban co
					clearBoard(tmpBoard22);
					//result.push_back(t);
				}
			}
		}
		else {
			//nguoc lai thi nuoc di do khong tao BAY
			
			//xoa ban co
			clearBoard(tmpCurrBoard);
			clearBoard(tmpPreBoard);
			return result;
		}

		//xoa ban co
		clearBoard(tmpCurrBoard);
		clearBoard(tmpPreBoard);
	}
	return result;
}

//tra ve danh sach cac nuoc di HOP LE cua player, dua tren ban co hien tai
vector<Move> get_valid_moves(int** current_board, int** previous_board, int player) {
	vector<Move> result;
	vector<Move> temp = bay_or_mo(current_board, previous_board, player);
	Position start, end;

	//copy trang thai ban co hien tai
	//previous_board = copy_board(current_board);

	//neu co nuoc di mo hoac bay
	if (temp.size() != 0) {
		result = temp;
		return result;
	}
	else {
		//tim nuoc di hop le
		for (int row = 0; row < 5; row++) {
			for (int col = 0; col < 5; col++) {
				int t = current_board[row][col];
				if (t == player) {
					start.x = row;
					start.y = col;
					vector<Position> ds = dsLanCan[row][col];
					for (unsigned int i = 0; i < ds.size(); i++) {
						if ((current_board[ds[i].x][ds[i].y] != 1) && (current_board[ds[i].x][ds[i].y] != -1)) {
							end.x = ds[i].x;
							end.y = ds[i].y;
							result.push_back(Move(start, end));
						}
					}
				}
			}
		}
	}

	return result;
}

//ham cat tia alpha-beta
int alphaBeta(int** currBoard, int** preBoard, Move vMove, int depth, int& alpha, int& beta, int player) {
	int soQuanChenhLech = 0;
	int value = 0;
	int enemy = 0;

	//Move* p = nullptr;

	if (depth == 0) {
			soQuanChenhLech = max(soQuanChenhLech, (int)(ganh(currBoard, vMove, player).size() + vay(currBoard, vMove, player).size()));
			return soQuanChenhLech = soQuanChenhLech * player;
	}
	else {
		if (player == 1) {
			value = -100000;
			int** tmpCurrBoard = copy_board(currBoard);
			int** tmpPreBoard = nullptr;

			tmpPreBoard = copy_board(currBoard);
			tmpCurrBoard[vMove.pos_start.x][vMove.pos_start.y] = 0;
			tmpCurrBoard[vMove.pos_end.x][vMove.pos_end.y] = player;
			cout << "-----\nbefore\n";
			print_board(tmpPreBoard);
			cout << "-----\nafter\n";
			print_board(tmpCurrBoard);
			print_board(tmpCurrBoard);
			cout << "----------\n";
			vector<Move> childMove = get_valid_moves(tmpCurrBoard, tmpPreBoard, player);
			
			tmpPreBoard = copy_board(tmpCurrBoard);
			for (unsigned int i = 0; i < childMove.size(); i++) {
				tmpCurrBoard[childMove[i].pos_start.x][childMove[i].pos_start.y] = 0;
				tmpCurrBoard[childMove[i].pos_end.x][childMove[i].pos_end.y] = player;
				cout << "-----\nbefore\n";
				print_board(tmpPreBoard);
				cout << "-----\nafter\n";
				print_board(tmpCurrBoard);
				cout << "----------\n";
				//vector<Move> childMove2 = get_valid_moves(tmpCurrBoard, tmpPreBoard, player);

				value = max(value, alphaBeta(tmpCurrBoard, tmpPreBoard, childMove[i], depth - 1, alpha, beta, -1));
				//tmpPreBoard = copy_board(tmpCurrBoard);

				alpha = max(alpha, value);
				if (value >= beta) {
					break; //cat tia beta
				}
			}

			////xoa ban co
			//clearBoard(tmpCurrBoard);
			//clearBoard(tmpPreBoard);

			return value;
		}
		else {
			value = 100000;
			int** tmpCurrBoard = copy_board(currBoard);
			int** tmpPreBoard = nullptr;

			tmpPreBoard = copy_board(currBoard);
			tmpCurrBoard[vMove.pos_start.x][vMove.pos_start.y] = 0;
			tmpCurrBoard[vMove.pos_end.x][vMove.pos_end.y] = player;
			cout << "-----\nbefore\n";
			print_board(tmpPreBoard);
			cout << "-----\nafter\n";
			print_board(tmpCurrBoard);
			cout << "----------\n";
			vector<Move> childMove = get_valid_moves(tmpCurrBoard, tmpPreBoard, player);

			tmpPreBoard = copy_board(tmpCurrBoard);
			for (unsigned int i = 0; i < childMove.size(); i++) {
				int** tmpCurrBoard22 = copy_board(tmpCurrBoard);
				tmpCurrBoard22[childMove[i].pos_start.x][childMove[i].pos_start.y] = 0;
				tmpCurrBoard22[childMove[i].pos_end.x][childMove[i].pos_end.y] = player;
				cout << "-----\nbefore\n";
				print_board(tmpPreBoard);
				cout << "-----\nafter\n";
				print_board(tmpCurrBoard);
				cout << "----------\n";
				//vector<Move> childMove2 = get_valid_moves(tmpCurrBoard, tmpPreBoard, player);

				value = min(value, alphaBeta(tmpCurrBoard, tmpPreBoard, childMove[i], depth - 1, alpha, beta, 1));
				//tmpPreBoard = copy_board(tmpCurrBoard);

				beta = min(beta, value);
				if (value <= alpha) {
					break; //cat tia alpha
				}
			}

			//xoa ban co
			//clearBoard(tmpCurrBoard);
			//clearBoard(tmpPreBoard);

			return value;
		}
	}
	return value;
}

//chon nuoc di toi uu
Move select_move(int** current_board, int** previous_board, int player) {

	//version 1 - chon ngau nhien
	//vector<Move> validMove = get_valid_moves(current_board, previous_board, player);
	//srand((int)time(NULL));
	//int index = rand() % validMove.size();
	//Move new_move = validMove[index];
	//return new_move;

	//version 2 - chon theo phuong phap minimax ket hop cat tia alpha-beta

	int** tmpCurrBoard = copy_board(current_board);
	int** tmpPreBoard = nullptr;
	int index = 0;
	if (previous_board != nullptr) {
		tmpPreBoard = copy_board(previous_board);
	}

	vector<Move> validMove = get_valid_moves(tmpCurrBoard, tmpPreBoard, player);

	//tim nuoc di toi uu
	int alphaMacDinh = -100000;	//alpha mac dinh ban dau la vo cung be
	int betaMacDinh = 100000;		//beta mac dinh ban dau la vo cung lon
	int depth = 6;
	vector<int> diemSo;

	for (unsigned int i = 0; i < validMove.size(); i++) {
		diemSo.push_back(alphaBeta(tmpCurrBoard, tmpPreBoard, validMove[i], depth, alphaMacDinh, betaMacDinh, player));
	}

	if (player == 1) {
		//index = max_element(diemSo.begin(), diemSo.end()) - diemSo.begin();
		int* maxValue = &diemSo[0];
		for (unsigned int i = 0; i < diemSo.size(); i++) {
			if (*maxValue < diemSo[i]) {
				maxValue = &diemSo[i];
			}
		}
		index = maxValue - &diemSo[0];
	}
	else if (player == -1) {
		//index = min_element(diemSo.begin(), diemSo.end()) - diemSo.begin();
		int* minValue = &diemSo[0];
		for (unsigned int i = 0; i < diemSo.size(); i++) {
			if (*minValue > diemSo[i]) {
				minValue = &diemSo[i];
			}
		}
		index = minValue - &diemSo[0];
	}

	//xoa ban co
	clearBoard(tmpCurrBoard);
	clearBoard(tmpPreBoard);

	return validMove[index];
}

//chon nuoc di toi uu test1
Move select_move_1(int** current_board, int** previous_board, int player) {

	//version 1 - chon ngau nhien
	//vector<Move> validMove = get_valid_moves(current_board, previous_board, player);
	//srand((int)time(NULL));
	//int index = rand() % validMove.size();
	//Move new_move = validMove[index];
	//return new_move;

	//version 2 - chon theo phuong phap minimax ket hop cat tia alpha-beta

	int** tmpCurrBoard = copy_board(current_board);
	int** tmpPreBoard = nullptr;
	int index = 0;
	if (previous_board != nullptr) {
		tmpPreBoard = copy_board(previous_board);
	}

	vector<Move> validMove = get_valid_moves(tmpCurrBoard, tmpPreBoard, player);

	//tim nuoc di toi uu
	int alphaMacDinh = -100000;	//alpha mac dinh ban dau la vo cung be
	int betaMacDinh = 100000;		//beta mac dinh ban dau la vo cung lon
	int depth = 2;
	vector<int> diemSo;

	for (unsigned int i = 0; i < validMove.size(); i++) {
		diemSo.push_back(alphaBeta(tmpCurrBoard, tmpPreBoard, validMove[i], depth, alphaMacDinh, betaMacDinh, player));
	}

	if (player == 1) {
		//index = max_element(diemSo.begin(), diemSo.end()) - diemSo.begin();
		int* maxValue = &diemSo[0];
		for (unsigned int i = 0; i < diemSo.size(); i++) {
			if (*maxValue < diemSo[i]) {
				maxValue = &diemSo[i];
			}
		}
		index = maxValue - &diemSo[0];
	}
	else if (player == -1) {
		//index = min_element(diemSo.begin(), diemSo.end()) - diemSo.begin();
		int* minValue = &diemSo[0];
		for (unsigned int i = 0; i < diemSo.size(); i++) {
			if (*minValue > diemSo[i]) {
				minValue = &diemSo[i];
			}
		}
		index = minValue - &diemSo[0];
	}

	//xoa ban co
	clearBoard(tmpCurrBoard);
	clearBoard(tmpPreBoard);

	return validMove[index];
}

//chon nuoc di toi uu test2
Move select_move_2(int** current_board, int** previous_board, int player) {

	//version 1 - chon ngau nhien
	//vector<Move> validMove = get_valid_moves(current_board, previous_board, player);
	//srand((int)time(NULL));
	//int index = rand() % validMove.size();
	//Move new_move = validMove[index];
	//return new_move;

	//version 2 - chon theo phuong phap minimax ket hop cat tia alpha-beta

	int** tmpCurrBoard = copy_board(current_board);
	int** tmpPreBoard = nullptr;
	int index = 2;
	if (previous_board != nullptr) {
		tmpPreBoard = copy_board(previous_board);
	}

	vector<Move> validMove = get_valid_moves(tmpCurrBoard, tmpPreBoard, player);

	//tim nuoc di toi uu
	int alphaMacDinh = -100000;	//alpha mac dinh ban dau la vo cung be
	int betaMacDinh = 100000;		//beta mac dinh ban dau la vo cung lon
	int depth = 50;
	vector<int> diemSo;

	for (unsigned int i = 0; i < validMove.size(); i++) {
		diemSo.push_back(alphaBeta(tmpCurrBoard, tmpPreBoard, validMove[i], depth, alphaMacDinh, betaMacDinh, player));
	}

	if (player == 1) {
		//index = max_element(diemSo.begin(), diemSo.end()) - diemSo.begin();
		int* maxValue = &diemSo[0];
		for (unsigned int i = 0; i < diemSo.size(); i++) {
			if (*maxValue < diemSo[i]) {
				maxValue = &diemSo[i];
			}
		}
		index = maxValue - &diemSo[0];
	}
	else if (player == -1) {
		//index = min_element(diemSo.begin(), diemSo.end()) - diemSo.begin();
		int* minValue = &diemSo[0];
		for (unsigned int i = 0; i < diemSo.size(); i++) {
			if (*minValue > diemSo[i]) {
				minValue = &diemSo[i];
			}
		}
		index = minValue - &diemSo[0];
	}

	//xoa ban co
	clearBoard(tmpCurrBoard);
	clearBoard(tmpPreBoard);

	return validMove[index];
}



//thuc hien nuoc di
void act_move(int** current_board, Move m, int player) {
	int mpStartY = m.pos_start.y;
	int mpStartX = m.pos_start.x;

	int mpEndY = m.pos_end.y;
	int mpEndX = m.pos_end.x;

	current_board[mpStartX][mpStartY] = 0;
	current_board[mpEndX][mpEndY] = player;
}

void play(int player) //int currPlayer, int** currBoard, int** prevBoard, int(&arr)[2], int& hetLuotDiHoacPhamLuat
{

	double thoiGianSuyNghi = 0; //thoi gian suy nghi
	int** board = init_board(); //khoi tao ban co ban dau
	int** pre_board = nullptr; //trang thai cua ban co truoc do
	print_board(board);
	int count = 0, limit = 50;
	int currPlayer = player;
	vector<Move> p;

	while (count < limit) {
		count++;

		cout << "----------------------------------------------\n";
		cout << "Luot thu: " << count << endl;
		cout << "\t\t\t\tplayer: " << currPlayer << endl;
		//lay danh sach cac nuoc di hop le
		vector<Move> valid_moves = get_valid_moves(board, pre_board, currPlayer);

		if (valid_moves.size() != 0) //neu co nuoc di hop le
		{
			if (valid_moves.size() == 1) {
				//neu chi co 1 nuoc di hop le
				p.push_back(valid_moves[0]);
			}
			else {
				//chon nuoc di toi uu
				if (currPlayer == 1) {
					//thoi gian bat dau
					//clock_t start = clock();

					p.push_back(select_move_1(board, pre_board, currPlayer));

					//thoi gian ket thuc
					//clock_t finish = clock();

					//thoi gian chon nuoc di
					//thoiGianSuyNghi = (double)(finish - start) / CLOCKS_PER_SEC;
					//cout << "Time: " << thoiGianSuyNghi << " s" << endl;

					//neu thoi gian chon nuoc di lau hon 3 giay thi ket thuc tro choi
					//nguoi choi o luot tiep theo chien thang
					// if (thoiGianSuyNghi > (double)3) {
					// 	cout << "Het gio! Ban bi xu thua." << endl;
					// 	return;
					// }
				}
				else if (currPlayer == -1) {
					//thoi gian bat dau
					//clock_t start = clock();

					p.push_back(select_move_2(board, pre_board, currPlayer));

					//thoi gian ket thuc
					//clock_t finish = clock();

					//thoi gian chon nuoc di
					//thoiGianSuyNghi = (double)(finish - start) / CLOCKS_PER_SEC;
					//cout << "Time: " << thoiGianSuyNghi << " s" << endl;

					//neu thoi gian chon nuoc di lau hon 3 giay thi ket thuc tro choi
					//nguoi choi o luot tiep theo chien thang
					//if (thoiGianSuyNghi > (double)3) {
					//	cout << "Het gio! Ban bi xu thua." << endl;
					//	return;
					//}
				}
			}

			cout << "Nuoc di toi uu: (" << p.back().pos_start.x << "," << p.back().pos_start.y << ")"
				<< "-> (" << p.back().pos_end.x << "," << p.back().pos_end.y << ")" << endl;
			
			//copy ban co hien tai
			pre_board = copy_board(board);

			////in ban co truoc do
			//cout << "\nTruoc: \t\n";
			//print_board(pre_board);
			//cout << endl;

			//thuc hien nuoc di, ban co hien tai la ban co moi
			act_move(board, p.back(), currPlayer);
			
			//kiem tra co an duoc quan doi thu hay khong
			vector<Position> g = ganh(pre_board, p.back(), currPlayer);
			unsigned int soQuanGanhDuoc = g.size();
			cout << "\t\t\t\tGanh:\n";
			for (unsigned int i = 0; i < g.size(); i++) {
				board[g[i].x][g[i].y] = currPlayer;
				cout << "\t\t\t\t(" << g[i].x << "," << g[i].y << ") = " << board[g[i].x][g[i].y] << endl;
			}

			vector<Position> v = vay(pre_board, p.back(), currPlayer);
			unsigned int soQuanVayDuoc = v.size();
			cout << "\n\t\t\t\tVay:\n";
			for (unsigned int i = 0; i < v.size(); i++) {
				board[v[i].x][v[i].y] = currPlayer;
				cout << "\t\t\t\t(" << v[i].x << "," << v[i].y << ") = " << board[v[i].x][v[i].y] << endl;
			}


		}
		else {
			//neu nguoi choi hien tai khong co nuoc di hop le nao thi tro choi ket thuc
			cout << "Nguoi choi " << currPlayer << " khong con nuoc di hop le nao." << endl;
			break;
		}
		//in ban co moi
		//cout << "\nSau: \t\n";
		print_board_move(pre_board, p.back());
		cout << endl;

		print_board(board);

		p.pop_back();
		currPlayer *= (-1);
	}

	unsigned int diemCuaPlayer1 = 0, diemCuaPlayer2 = 0;
	int doiThu = player * (-1);

	for (unsigned int row = 0; row < 5; row++) {
		for (unsigned int col = 0; col < 5; col++) {
			if (board[row][col] == player) {
				diemCuaPlayer1++;
			}
			if (board[row][col] == doiThu) {
				diemCuaPlayer2++;
			}
		}
	}
	cout << "\n\t\tNguoi di truoc la: " << player;
	cout << "\n\t\tNguoi chien thang la: ";
	if (diemCuaPlayer1 > diemCuaPlayer2) {
		cout << player << endl;
	}
	else {
		cout << doiThu << endl;
	}
	cout << "\t\tTy so chung cuoc: " << diemCuaPlayer1 << " - " << diemCuaPlayer2 << endl;

	//xoa ban co
	clearBoard(board);
	clearBoard(pre_board);

	return;
}

int main()
{
	play(1); //nguoi choi 1 di truoc

	return 0;
}
