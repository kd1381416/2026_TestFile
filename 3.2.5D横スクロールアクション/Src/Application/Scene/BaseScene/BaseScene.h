#pragma once
#include"json.hpp"

class BaseScene
{
public :

	BaseScene()			 { Init(); }
	virtual ~BaseScene() {}

	void PreUpdate();
	void Update();
	void PostUpdate();

	void PreDraw();
	void Draw();
	void DrawSprite();
	void DrawDebug();

	// オブジェクトリストを取得
	const std::list<std::shared_ptr<KdGameObject>>& GetObjList()
	{
		return m_objList;
	}
	
	// オブジェクトリストに追加
	void AddObject(const std::shared_ptr<KdGameObject>& _obj)
	{
		m_objList.push_back(_obj);
	}

	//jsonロード
	void JsonLoad(const std::string& _fileName, nlohmann::json& _json)
	{
		std::ifstream file("Json/" + _fileName + ".json");

		if (!file.is_open())
		{
			assert(0 && "Jsonファイルパスが間違っています");
			return;
		}

		//ifstreamから_jsonに情報を上書き
		file >> _json;

		file.close();
	}

	//jsonセーブ
	void JsonSave(const std::string& _filePath, const nlohmann::json& _json)
	{
		std::ofstream file("Json/" + _filePath + ".json");

		if (!file.is_open())
		{
			assert(0 && "Jsonファイルパスが間違っています");
			return;
		}

		//_jsonからofstream(ファイル)に情報を上書き
		//dump(情報の書式(インデント)指定)
		file << _json.dump(4);

		file.close();
	}

protected :

	// 継承先シーンで必要ならオーバーライドする
	virtual void Event();
	virtual void Init();

	std::unique_ptr<KdCamera> m_camera = nullptr;

	// 全オブジェクトのアドレスをリストで管理
	std::list<std::shared_ptr<KdGameObject>> m_objList;

	nlohmann::json m_Json;
};
