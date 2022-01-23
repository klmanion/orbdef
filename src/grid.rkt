;;;; grid
;; the underlying representation of the world

#lang racket/base

(require racket/function
         racket/draw
         racket/class racket/class/iop
         racket/gui/base
         racket/contract)

(module+ test
  (require rackunit))

(require "cell.rkt")

(provide grid<%> grid%)

(define grid<%>
  (interface ()
             get-dim-y get-dim-x
             draw))

(define/contract grid%
  (class/c
    (init-field
      [dim-y natural-number/c]
      [dim-x natural-number/c])

    (field
      [base vector/c])

    (get-dim-y (->m natural-number/c))
    (get-dim-x (->m natural-number/c))               

    (draw ((is-a?/c dc<%>) . ->m . any)))

  (class* object% (grid<%>)
    (super-new)

    (init-field
      [dim-y #f]
      [dim-x #f])

    (field [base
            (build-list
              dim-y
              (λ (y)
                (build-list
                  dim-x
                  (λ (x)
                    (new cell% [pos-y y] [pos-x x])))))])

    (define/public get-dim-y
      (λ ()
        dim-y))
    
    (define/public get-dim-x
      (λ ()
        dim-x))

    (define/public draw
      (λ (dc)
        (for-each (λ (lst)
                    (for-each (λ (e)
                                (send e draw dc))
                              lst))
                  base)))))
   

(module+ test
  (void))
