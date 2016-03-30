#!/usr/bin/env gosh
(use al)
(use gauche.uvector)
(use gauche.collection)

(alut-init '())

(define buf (al-gen-buffer))
(define pcm (alut-load-wav-file "chime.wav"))
(al-buffer-data buf pcm)
(define src (al-gen-source))
(al-source src AL_BUFFER buf)
;(al-source src AL_PITCH 1.0)
;(al-source src AL_GAIN 1.0)
;(al-source src AL_POSITION #f32(0 0 0))
;(al-source src AL_VELOCITY #f32(0 0 0))
;(al-source src AL_LOOPING #f)

;(al-listener AL_POSITION #f32(0 0 0))
;(al-listener AL_VELOCITY #f32(0 0 0))
;(al-listener AL_ORIENTATION #f32(0 0 -1 0 0 0))

(al-source-play src)
(do ()
    ((eqv? (al-get-source src AL_SOURCE_STATE) AL_STOPPED))
  (sys-sleep 1))

(sys-sleep 1) ; to avoid noise
(alut-exit)

