#pragma once
#include"json.hpp"

//						↓全てのObjectに継承する
class Player : public KdGameObject	//地面
{
public:
	Player() {}
	~Player() {};

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	void SetJson(nlohmann::json& _json) { m_Json = _json; }

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

private:

	//ModelやTextureはポインタで管理
	std::shared_ptr<KdSquarePolygon>	m_Polygon;

	//座標
	Math::Vector3	m_Pos;

	//アニメーション用
	float			m_Anime = 0.0f;

	//重力
	float			m_Gravity = 0;

	nlohmann::json	m_Json;
};