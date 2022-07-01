//Gateに表示している数字の符号を操作するクラス

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GateCode : MonoBehaviour
{
    //＋,ー,×のマテリアル
    [SerializeField]
    private Material[] CodeMaterial;

    //Gate参照
    private GameObject gate;
    //Gateスクリプト参照
    private Gate gateScript;

    void Start()
    {
        //各要素参照したり初期化したりする

        gate = transform.root.gameObject;
        gateScript = gate.GetComponent<Gate>();

        //GateTypeに応じた符号のマテリアルになるようにする
        if (gate.transform.tag == "PlusGate")
        {
            this.GetComponent<Renderer>().material = CodeMaterial[0];
        }
        if (gate.transform.tag == "MinusGate")
        {
            this.GetComponent<Renderer>().material = CodeMaterial[1];
        }
        if (gate.transform.tag == "MultiplicationGate")
        {
            this.GetComponent<Renderer>().material = CodeMaterial[2];
        }
    }

}
