;;
;; al.scm
;;
;;   Copyright (c) 2005 KOGURO, Naoki
;;   All rights reserved.
;;
;;   Redistribution and use in source and binary forms, with or without 
;;   modification, are permitted provided that the following conditions 
;;   are met:
;;
;;   1. Redistributions of source code must retain the above copyright 
;;      notice, this list of conditions and the following disclaimer.
;;   2. Redistributions in binary form must reproduce the above copyright 
;;      notice, this list of conditions and the following disclaimer in the 
;;      documentation and/or other materials provided with the distribution.
;;   3. Neither the name of the authors nor the names of its contributors 
;;      may be used to endorse or promote products derived from this 
;;      software without specific prior written permission.
;;
;;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
;;   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
;;   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
;;   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
;;   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;;   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
;;   TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
;;   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
;;   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
;;   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
;;   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;;
;; $Id$

(define-module al
  (use gauche.collection)
  (use gauche.uvector)
  (use srfi-2)
  (export-all))

(select-module al)
(dynamic-load "al")

(define (al-gen-buffer)
  (and-let* ((vec (al-gen-buffers 1)))
    (ref vec 0)))

(define (al-delete-buffer buf)
  (al-delete-buffers (make-u32vector 1 buf)))

(define (al-gen-source)
  (and-let* ((vec (al-gen-sources 1)))
    (ref vec 0)))

(define (al-delete-source src)
  (al-delete-sources (make-u32vector 1 src)))

(provide "al")

