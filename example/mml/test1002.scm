;; -*- coding: utf-8 -*-
;;
;; MML演奏テスト
;; 2025-8-12
;;
(add-load-path "." :relative)
(use al)
(use mmlproc)
(use gauche.uvector)
(use gauche.vport)

;; 変数
(define pcm-raw  #f) ; PCMの生データ
(define wav-data #f) ; WAVデータ
(define buf #f)      ; Gauche-alのバッファ情報
(define pcm #f)      ; Gauche-alのPCMデータ情報
(define src #f)      ; Gauche-alのソース情報

;; 初期化
(set! mml-sample-rate 44100)
(alut-init '())

;; MML文字列を読み込んでWAVデータに変換
(print "mml->wav")
($ set! pcm-raw $ mml->pcm $ string-append
   "t90 !c0 @501 o4 "
   "  bag   | e8a8ge | d8d8gg | a2.   "
   "  bb>d< | b8b8ag | e8e8da | g2.   "
   "!c1 @501 o3 v90 "
   "  g2.   | c2.    | g2.    | d2.   "
   "  g2.   | g2.    | cd2    | g2.   "
   "!c2 @501 o3 v90 "
   "  b2.   | e2.    | b2.    | f#2.  "
   "  b2.   | b2.    | ef#2   | b2.   "
   "!c3 @501 o3 v90 "
   "  >d2.< | g2.    | >d2.<  | a2.   "
   "  >d2.< | >f2.<  | g>c2<  | >d2.< "
   )
(set! wav-data (make-u8vector (get-wav-size pcm-raw)))
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
(until (= (al-get-source src AL_SOURCE_STATE) AL_STOPPED)
  (sys-nanosleep (* 100 1000000))) ; 100msec
(print "finished.")

;; 終了
(sys-sleep 1) ; 少し待たないとノイズが出る
(alut-exit)

