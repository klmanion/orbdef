;;;; pos
;; position datatype

#lang racket/base

(require racket/function
         racket/class racket/class/iop
         racket/contract)

(provide pos<%> pos%)

(define pos<%>
  (interface ()
             get-yx set-yx
             is-valid?))

(define/contract pos%
  (class/c
    (init-field
      [y (or/c #f integer?)]
      [x (or/c #f integer?)])

    (get-yx (->m (values integer? integer?)))
    (set-yx (integer? integer? . ->m . any))

    (is-valid? (->m boolean?)))

  (class* object% (pos<%>)
    (super-new)

    (init-field
      [y #f]
      [x #f])

    (define/public get-yx
      (λ ()
        (values y x)))

    (define/public set-yx
      (λ (ny nx)
        (set! y ny)
        (set! x nx)))

    (define/public is-valid?
      (λ ()
        (and (not (eq? y #f))
             (not (eq? x #f)))))))     

