# GraphicProgrammingAssignment
Degree-Y2S2  Project

## About Including Libraries
Please include your libraries in pch.h to prevent include conflicts.

After adding your libraries, whenever you create a new class or any .cpp file,
you must write the following line at the very top of the file:
``#include "pch.h"``
(See the example image.)
!["Include pch.h"](includePCH.png "Inlcude pch.h at first line of cpp file")

Then you need to : 
1. right-click the ``.cpp`` file
2. Select **Properties**
3. Go to **Precompiled Headers**
4. Set **Precompiled Header** to **Use(/Yu)**
5. Set **Precompiled Header File** to **pch.h**
6. Click **Apply**

**Warm Reminder** 
Do not define macros that you frequently modify in **pch.h.**
Otherwise, every time you change those macros, the entire project needs to recompile,
which will take longer - save yourself the trouble! 😂