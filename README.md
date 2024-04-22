This is an implementation of the Runlength descriptors for document image representation described in [1].
These descriptors can be compared using similarity/distance measures such as the dot-product or Euclidean distance.
The implementation is different from the one on the paper, but results should be quite similar.
The core of the implementation is in C, with a Matlab wrapper to ease its use.
It has only been tested under linux and mac, but should work without problems under other systems.

run demo.m to compile the mex file and compute the runlength descriptor of a sample image.

Please cite [1] if you use this software in your technical work.

[1] Large-scale document image retrieval and classification with runlength histograms and binary embeddings.
A. Gordo, F. Perronnin, and E. Valveny.
In Pattern Recognition, 2012.


THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.

