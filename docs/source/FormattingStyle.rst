Formatting Style
================

Inside a string, a formatting token is in the format ``{...}`` where ``...`` are
the formatting flags for that token. Literally any variable can be passed as
format arg as long as there is an std::ostream ``operator<<`` defined for it's
type.

Formatting Flags
----------------

Formatting flags are colon (``:``) seperated flags inside a formatting token.
They can be used to control how the variable is represented in the output
string.

These operate on the string output of ``operator<<``, so, they know nothing
about the variable itself, only it's string representation.

Do note that these are **order dependant**, so, ``{x:wl4}`` is not the same as
``{wl4:x}`` because these are applied in order from left to right and might
effect the output.

``b`` flag
^^^^^^^^^^

It outputs ``true`` if the string contains a non-zero number,
otherwise outputs ``false``.

Basically, it mimics the behaviour of ``std::boolalpha``.

Format: ``{b}``

Example: ``Format("{b}", true)`` will return ``"true"``.


``o`` flag
^^^^^^^^^^

It outputs the octal representation of the number contained
in the string.

Basically, it mimics the behaviour of ``std::oct``.

Format: ``{o}``

Example: ``Format("{o}", 255)`` will return ``"377"`` (377 is octal for 255 in decimal).

``x`` flag
^^^^^^^^^^

It outputs the hexadecimal representation of the number
contained in the string.

Basically, it mimics the behaviour of ``std::hex``.

Format: ``{x}``

Example: ``Format("{x}", 255)`` will return ``"ff"`` (ff is hexadecimal for 255 in decimal).

``f`` flag
^^^^^^^^^^

It outputs the fixed-precision representation of
the floating-point number contained in the string.
Default width is 6.

Basically, it mimics the behaviour of ``std::fixed``.

Format: ``{f}``

Example: ``Format("{f}", 3.0)`` will return ``"3.000000"``.

``wl`` flag
^^^^^^^^^^^

It outputs the string of size ``width`` or more by adding
leading spaces to the string.

Format: ``{wl<width>}``

Example: ``Format("{wl10}", "Leading")`` will return ``"    Leading"``.

``wt`` flag
^^^^^^^^^^^

It outputs the string of size ``width`` or more by adding
trailing spaces to the string.

Format: ``{wt<width>}``

Example: ``Format("{wt10}", "Trailing")`` will return ``"Trailing  "``.

``wc`` flag
^^^^^^^^^^^

It outputs the string of size ``width`` or more by adding
leading and trailing spaces to the string. It also centralizes the
content.

In case of odd number of spaces, there are
``(n - 1) / 2`` leading spaces and ``(n + 1) / 2`` trailing spaces with
``n`` as total number of spaces to add.

Format: ``{wc<width>}``

Example: ``Format("{wc10}", "Centered")`` will return ``" Centered "``.

``wi`` flag
^^^^^^^^^^^

It outputs the string of size ``width`` or more containing a number. If the
width of number is shorter, leading ``'0'`` s are used.

Basically, it mimics the behaviour of ``std::setw(width)<<std::setfill('0')``.

Format: ``{wi<width>}``

Example: ``Format("{wi4}", 20)`` will return ``"0020"``.

``wf`` flag
^^^^^^^^^^^

It outputs the string of size ``width`` or more containing a floating-point
number. If the width of the fractional part of the number is shorter,
trailing ``'0'`` s are used.

Basically, it mimics the behaviour of ``std::setprecision(width)<<std::fixed)``.

Format: ``{wf<width>}``

Example: ``Format("{wf4}", 20)`` will return ``"20.0000"``.

``cxxxxx`` flag
^^^^^^^^^^^^^^^

It changes the color of stream. It's argument must always be an empty string.
The first 3 characters after ``c`` are for color codes which can be the
following:

* ``wht`` - White
* ``red`` - Red
* ``grn`` - Green
* ``blu`` - Blue
* ``ylw`` - Yellow
* ``cyn`` - Cyan
* ``pnk`` - Pink

The last two characters are for bold and italic respectively. The character for
bold must be ``'b'`` to enable bold and the character for italic must be ``'i'``
to enable italic. Any other value will be leave the respective options disabled
but using ``'x'`` for disabled is recommended for uniformness.

Format: ``{c<wht|red|grn|blu|ylw|cyn|pnk><b|x><i|x>}``

Example: ``std::cout<<Format("{credbi}Hello{cwhtxx}\n", "");`` will print ``"Hello"``
in red with bold and italics. It will also restore the color to white with no bold or
italics.

Combinations
------------

All these flags can be combined to achieve behaviour unachievable
by using them individually.

Example - ``{x:wi8}`` will output a hexadecimal number of width 8 and
``{x:wc10}`` will pad the hexadecimal output almost equally on both
sides which is very useful in table-like output.
