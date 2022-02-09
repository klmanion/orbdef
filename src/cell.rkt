;;;; cell
;; element of the grid

#lang racket/base

(require racket/function
         racket/draw
         racket/class racket/class/iop
         racket/gui/base
         racket/contract)

(require "pos.rkt")

(module+ test
  (require rackunit))

(provide cell<%> cell%)

(define cell<%>
  (interface (pos<%>)
             set-content draw))

(define/contract cell%
  (class/c
    (field
      [content string?])

    (draw ((is-a?/c dc<%>) integer? integer? . ->m . any)))

  (class* pos% (cell<%>)
    (init-field pos-y pos-x)
    (super-new [y pos-y] [x pos-x])

    (field
      [occupants '()]
      [content " "])

    (inherit-field y x)

    (define/public set-content
      (λ (nc)
        (set! content nc)))

    (define/public draw
      (λ (dc yoff xoff)
        (let ([y (+ (* (send dc get-char-height) y) yoff)]
              [x (+ (* (send dc get-char-width) x) xoff)])
          (send dc draw-text content x y))))))

(module+ test
  (void))
