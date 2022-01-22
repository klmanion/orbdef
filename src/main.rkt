;;;; Orbital Defense (orbdef)
;; created by Kurt L. Manion
;; on: 22 Jan 2021
;;;
;; A rouge-like economy-based wargame.
;;
;; Control your war-machine through proliferating levels of abstraction.
;;

#lang racket/base

(require racket/draw
         racket/function
         racket/class racket/class/iop
         racket/gui/base
         racket/contract
         lux lux/chaos/gui lux/chaos/gui/mouse lux/chaos/gui/key)
(module+ test
  (require rackunit))

(struct word () 
  #:mutable
  #:methods gen:word
  [(define word-label
     (λ (s ft)
       "Orbital Defense"))

   (define word-tick
     (λ (w)
       w))

   (define word-event
     (λ (w e)
       w))

   (define word-output
     (λ (w)
       (lambda (width height dc)
         (send dc set-background "black")
         (send dc clear)
         (send dc set-text-foreground "white")
         (send dc draw-text "hello world"
               (- (/ width 2) (* (send dc get-char-width) 5))
               (/ height 2)))))])

(module+ main
  (call-with-chaos
    (make-gui)
    (thunk
      (fiat-lux (word))))) 

(module+ test
  (void))

;; vi: set lisp expandtab tw=79:
