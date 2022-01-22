;;;; clock
;; monitor of elapsed program and game time

#lang racket/base

(require racket/function
         racket/class racket/class/iop
         racket/contract)
(module+ test
  (require rackunit))

(provide clock<%> clock%)

(define-interface clock<%> ()
                  (tick get-ticks 
                   step get-steps
                   is-paused? is-unpaused? set-pause pause unpause pause-toggle
                   set-ticks-per-step get-steps-per-sec))

(define/contract clock%
  (class/c
    (field
      [tick-rate natural-number/c]
      [ticks natural-number/c]
      [counter natural-number/c]
      [steps natural-number/c]
      [paused boolean?]
      [ticks-per-step natural-number/c])

    (tick (->m void?))
    (get-ticks (->m natural-number/c))

    (step (->m void?))
    (get-steps (->m natural-number/c))

    (is-paused? (->m boolean?)) 
    (set-pause (natural-number/c . ->m . void?))
    (pause (->m void?))
    (unpause (->m void?))
    (pause-toggle (->m void?))

    (set-ticks-per-step (natural-number/c . ->m . void?))
    (get-steps-per-sec (->m natural-number/c)))

  (class* object% (clock<%>)
    (super-new)

    (field
      [tick-rate 60] 
      [ticks 0]
      [counter 0]
      [steps 0]
      [paused #f]
      [ticks-per-step 10]) 
    
    (define/public tick
      (λ ()
        (set! ticks (add1 ticks))
        (when (is-unpaused?)
          (set! counter (add1 counter)))
        (when (= (modulo counter ticks-per-step) 0)
          (step))))

    (define/public get-ticks
      (λ ()
        ticks))

    (define/public get-tick-rate
      (λ ()
        tick-rate))
;;;
    (define/public step
      (λ ()
        (set! steps (add1 steps))))

    (define/public get-steps
      (λ ()
        steps))
;;;
    (define/public is-paused?
      (λ ()
        paused))

    (define/public is-unpaused?
      (λ ()
        (not (is-paused?)))) 

    (define/public set-pause
      (λ (npause)
        (set! paused npause)))

    (define/public pause
      (λ ()
        (set-pause #t)))

    (define/public unpause
      (λ ()
        (set-pause #f)))

    (define/public pause-toggle
      (λ ()
        (set-pause (not paused))))
;;;
    (define/public set-ticks-per-step
      (λ (n)
        (set! ticks-per-step n)))

    (define/public get-steps-per-sec
      (λ ()
        (/ tick-rate ticks-per-step)))))

