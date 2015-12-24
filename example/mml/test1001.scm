;; -*- coding: utf-8 -*-
;;
;; MML演奏テスト
;; 2015-12-24
;;
(add-load-path "." :relative)
(use al)
(use mmlproc)
(use gauche.uvector)
(use gauche.vport)

;; 変数
(define pcm-raw  #f) ; PCMの生データ
(define wav-data #f) ; WAVデータ
(define buf #f) ; Gauche-alのバッファ情報
(define pcm #f) ; Gauche-alのPCMデータ情報
(define src #f) ; Gauche-alのソース情報

;; 初期化
(set! mml-sample-rate 22050)
(alut-init '())

;; MML文字列を読み込んでWAVデータに変換
(print "mml->wav")
(set! pcm-raw (mml->pcm (string-append
  "!c0 @500 o4 "
  "  d8b8a8g8d2 | d8b8a8g8e2      | e8>c8<b8a8f+2       | >d8d8c8<a8b2  "
  "  d8b8a8g8d2 | d8b8a8g8e2      | e8>c8<b8a8>d8d8d8d8 | e8d8c8<a8g>d< "
  "  b8b8bb8b8b | b8>d8<g8.a16b2> | c8c8c8c8c8<b8b8b8   | b8a8a8g8a>d<  "
  "  b8b8bb8b8b | b8>d8<g8.a16b2> | c8c8c8c8c8<b8b8b8   | >d8d8c8<a8g2  "
  )))
(set! wav-data (make-u8vector (+ (* (s16vector-length pcm-raw) 2) (* 11 4))))
(let1 out (open-output-uvector wav-data)
  (unwind-protect
   (write-wav pcm-raw out)
   (close-output-port out)))

;; Gauche-alでWAVデータを読み込んで再生
(print "play")
(set! buf (al-gen-buffer))
(set! pcm (alut-load-wav-memory wav-data))
(al-buffer-data buf pcm)
(set! src (al-gen-source))
(al-source src AL_BUFFER buf)
(al-source-play src)
(while (not (eq? (al-get-source src AL_SOURCE_STATE) AL_STOPPED))
  (sys-nanosleep (* 100 1000000)) ; 100msec
  )
(print "finished.")

;; 終了
(sys-sleep 1) ; 少し待たないとノイズが出る
(alut-exit)

