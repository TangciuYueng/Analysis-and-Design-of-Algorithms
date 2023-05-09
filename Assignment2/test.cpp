#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

clock_t start_,end_;

using namespace std;

bool searchMatrix(vector<vector<int> >& matrix, int target){
    //TODO
    // 获得矩阵的维度 
    int m = matrix.size();
	int n = matrix[0].size();
	// 从左上角开始 
	int i = 0;
	int j = n - 1;
	// 保证不越界
	while (i < m && i >= 0 && j < n && j >= 0) {
		// 正好是要找的 
		if (matrix[i][j] == target)
			return true;
		// 第i行的最大都比target小说明整行都比target小
		// 移动到下一行寻找 
		else if (matrix[i][j] < target) 
			++i;
		// 当前比target更大，向左找更小的 
		else
			--j; 
	} 
	// 找不到
	return false; 
}


int main(){
	
//	读取测试数据 
    ifstream inFile("testcase.csv", ios::in);
    string lineStr;
    
    start_ = clock();
    

	if (!inFile.is_open())
	{
		cout<<"Error!"<<endl;
	}
	
//	测试结果标记
	int correct_num = 0;
	int error_num = 0;
	

//	运行测试数据，输出结果 
    while (getline(inFile, lineStr))
    {
    	vector<vector<int>> matrix;
		
    	string number;
    	bool num_end = false;
    	bool line_end = false;
    	int target = -1;
    	bool result;
    	vector<int> line;
    	for(int i=0; i<lineStr.size(); i++){
    		if (!num_end){
	    		if (lineStr[i] == '['){
	    			line_end = false;
	    			line.clear();
				}
				else if (lineStr[i] == ']' && line_end){
					number = "";
					num_end = true;
				}
	    		else if (lineStr[i] == ']' && !num_end){
	    			line.push_back(atoi(number.c_str()));
	    			matrix.push_back(line);
	    			line_end = true;
	    			number = "";
				}
				
				else if (lineStr[i] >= '0' && lineStr[i] <= '9')number += lineStr[i];
				else if (lineStr[i] == ',' && !line_end){
					line.push_back(atoi(number.c_str()));
					number = "";
				}
			}
			else{
				if (target == -1){
					if (lineStr[i] >= '0' && lineStr[i] <= '9')number += lineStr[i];
					else if (lineStr[i] == ',' && number != "")target = atoi(number.c_str());
				}
				else result = lineStr[i]-'0';
			}
		}
		if (result == searchMatrix(matrix,target))correct_num += 1;
		else error_num += 1;
	}
	end_ = clock();
	double endtime = (double)(end_ - start_)/CLOCKS_PER_SEC;
	inFile.close();
	
	cout<<"correct:"<<correct_num<<endl;
	cout<<"error:"<<error_num<<endl;
	cout<<"用时:"<<endtime*1000<<"ms"<<endl;
	
	system("pause");
	
	return 0;
}
