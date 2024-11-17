#pragma once
#include	<unordered_map>
#include <string>

// リソース管理サーバ
// すべて静的メンバで構成する
class ResourceServer {
public:
	static void	Init();
	static void	Release();

	static void	ClearGraph();
	static int	LoadGraph(const TCHAR* FileName);
	static int	LoadDivGraph(const TCHAR* FileName, int AllNum,
		int XNum, int YNum,
		int XSize, int YSize, int* HandleBuf);
	static int LoadModel(const TCHAR* FileName);

	static int	LoadSoundMem(const TCHAR* FileName);

	static void DeleteGraph(int GraphHandle);
	static void DeleteModel(int ModelHandle);

 private:
	 static std::unordered_map<std::string, int>	_mapGraph;
	typedef struct {
		int		AllNum;
		int* handle;
	} DIVGRAPH;
	static std::unordered_map<std::string, DIVGRAPH>	_mapDivGraph;
	// _mapModelに関してはモデルのハンドルを使いまわせるか、お試し（モデルの保持によりメモリが圧迫されたりするようであれば都度考える）
	static std::unordered_map<std::string, int> _mapModel;

	static std::unordered_map<std::string, int>	_mapSound;
};

