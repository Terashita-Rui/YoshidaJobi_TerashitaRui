﻿//SEを繰り返し鳴らすクラス

using UnityEngine;
using System.Collections;
using System.Collections.Generic;

[RequireComponent(typeof(AudioSource))]
public class soundplayback : MonoBehaviour
{
    //AudioClip
    [SerializeField]
    AudioClip[] clips;
    [SerializeField]
    bool randomizePitch = true;
    [SerializeField]
    float pitchRange = 0.1f;

    protected AudioSource source;

    private void Awake()
    {
        // アタッチしたオーディオソースのうち1番目を使用する
        source = GetComponents<AudioSource>()[0];
    }

    //足音鳴らす
    public void PlayFootstepSE()
    {
        if (randomizePitch)
            source.pitch = 1.0f + Random.Range(-pitchRange, pitchRange);

        source.PlayOneShot(clips[Random.Range(0, clips.Length)]);
    }
}
