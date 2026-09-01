# PySS | Python Syntax Based Stylesheets
> [!CAUTION]
> PySS is in development and the fully working version is not completed yet. Features listed below can be removed, modified or may not ship at all.

> [!NOTE]
> This project isn't meant for production use or professional use as this is a hobby project. Will contains alot of bugs and things that won't be fixed anytime soon.
> This project is currently aimed to develop and work on Windows with no support for Unix system, additions on supported OS may come but currently only targeted for Windows.

**PySS** Allows you to create stylesheets like css with more simplicity, less hassle and with more features like
- No syntax overloads such as `{}`, `;` or `@`
- Native **Tailwind CSS** support
- Snippets for reusing multiple blocks of scripts or styling later
- Native **Regex (Regular Expressions)** for advanced property calling
- Single line comment support with `// Example Comment`
- Element and rule nesting and parent def recalling
- Simple breakpoint notation support (Tailwind CSS)
- HEX Code alpha support with `/`, `#FFFFFF/FF`
- Multiproperty declaration such as `padding-x`, `padding-lt`
> [!IMPORTANT]
> PySS script isn't supported on any major browsers natively and just like SCSS and SASS, PySS will be converted to native CSS through a compiler made in C.

## PySS Example with CSS
### PySS
> [!WARNING]
> The following example PySS script does not include every feature of PySS.
> The syntax and rules written in the example PySS script are prone to changes as we reach the first working verison.
```python
// Single line comment support
def * // Simple keyword Property declaration
    padding, margin = 0 // Property grouping support
    border, outline, text-decoration = none
    box-sizing = border-box

def :root
    --main-color: use color-blue-700 // Object oriented declaration

// Header Styling
def header
    use flex justify-between px-10
    width = 100%
    use bg-white // Native Tailwind CSS support
    height = auto

    // Element nesting support
    def .logo
        use size-xl
        color = --main-color // Functionless variable calling
        transition = .2s
        def :hover (color = black) // Single-line Property declaration
    
    // Navigation styling
    def .nav
        color = black
        use hover:text-grey
        gap = 10px
```
### CSS
```css
/* No single line comment support */
* { /* No simple property declaration */
    padding: 0; /* No property grouping support */
    margin: 0; /* Useless ; syntax hassle */
    border: none;
    outline: none;
    text-decoration: none;
    box-sizing: border-box;
} /* Useless {} syntax hassle */

:root {
    --main-color: blue; /* No object oriented declaration support */
}

/* Header Styling */
header {
    /* No native tailwind support */
    display: flex;
    justify-content: space-between;
    padding-left: 10rem;
    padding-right: 10rem;

    width: 100%;
    background-color: white;
    height: auto;
}

/* Parent recalling and no nesting support */
header .logo {
    /* No native tailwind css support */
    height: 20rem;
    width: 20rem;

    color: var(--main-color) /* No functionless variable calling */
    transition: .2s;
}

/* No nesting pseudoproperty support */
header .logo:hover {
    color: black;
}

/* Navigation Styling */
header .nav {
    color: black;
    /* No nesting pseudoproperty or tailwind css support */
    gap: 10px;
}

/* Parent recalling for pseudoproperty and no tailwind css support */
header .nav:hover {
    color: grey; /* No tailwind css support */
}
