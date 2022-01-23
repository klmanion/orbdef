;;;; world
;; brings together space, time, and the occupying entities

#lang racket/base

(require racket/draw
         racket/function
         racket/class racket/class/iop
         racket/gui/base
         racket/contract)

(require "clock.rkt")
(require "grid.rkt")

(provide world<%> world%)

(define world<%>
  (interface ()
             get-time
             on-step
             draw))
             
(define/contract world%
  (class/c
    (field
      [time (is-a?/c clock<%>)]
      [space (is-a?/c grid<%>)])
    
    (get-time (->m (is-a?/c clock<%>)))

    (on-step (->m void?))

    (draw ((is-a?/c dc<%>) natural-number/c natural-number/c . ->m . void?)))

  (class* object% (world<%>)
    (super-new)

    (field
      [time (new clock% [on-step (thunk
                                   (send this on-step))])]
      [space (new grid% [dim-y 27] [dim-x 80])])
    
    (define/public get-time
      (λ ()
        time))
     
    (define/public on-step
      (λ ()
        (void)))

    (define/public draw
      (λ (dc height width)
        (send* dc
               (set-background "black")
               (set-text-foreground "white")
               (clear)) 
        (send space draw dc height width)))))

(module+ test
  (require rackunit))
