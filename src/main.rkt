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

(require "clock.rkt")
(require "world.rkt")

(module+ test
  (require rackunit))

(struct word (world) 
  #:mutable
  #:methods gen:word
  [(define word-label
     (λ (s ft)
       "Orbital Defense"))

   (define word-tick
     (λ (w)
       (let* ([world (word-world w)]
              [time (send world get-time)])
         (send time tick))
       w))

   (define word-event
     (λ (w e)
       (let* ([world (word-world w)]
              [time (send world get-time)])
         (cond
           ([key-event? e]
            (let ([kc (send e get-key-code)])
              (cond [(equal? kc #\space)
                     (send time pause-toggle)]
                    [(equal? kc #\.)
                     (send time step)])))))
       w))

   (define word-output
     (λ (w)
       (lambda (width height dc)
         (let ([world (word-world w)])
           (send world draw dc height width)))))])

(module+ main
  (call-with-chaos
    (make-gui)
    (thunk
      (fiat-lux (word
                  (new world%)))))) 

(module+ test
  (void))

;; vi: set lisp expandtab tw=79:
