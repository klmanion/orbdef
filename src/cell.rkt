;;;; cell
;; element of the grid

#lang racket/base

(require racket/function
         racket/draw
         racket/class racket/class/iop
         racket/gui/base
         racket/contract)

(module+ test
  (require rackunit))

(provide cell<%> cell%)

(define cell<%>
  (interface ()))

(define/contract cell%
  any/c

  (class* object% (cell<%>)
    (super-new)

    (init-field
      [pos-y #f]
      [pos-x #f])

    (field
      [content "o"])

    (define/public draw
      (λ (dc yoff xoff)
        (let ([y (+ (* (send dc get-char-height) pos-y) yoff)]
              [x (+ (* (send dc get-char-width) pos-x) xoff)])
          (send dc draw-text content x y))))))

(module+ test
  (void))
