;;;
;;; Test al
;;;

(use gauche.test)

(test-start "al")
(use al)
(test-module 'al)

;; The following is a dummy test code.
;; Replace it for your tests.
;(test* "test-al" "al is working"
;       (test-al))

;; If you don't want `gosh' to exit with nonzero status even if
;; the test fails, pass #f to :exit-on-failure.
(test-end :exit-on-failure #t)




