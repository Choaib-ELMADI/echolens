from random_selection import *
import numpy as np
import cv2


def random_color_shift(image_path):
    image = cv2.imread(image_path)
    b, g, r = cv2.split(image)

    random_set, random_set_10_or_11, random_list = generate_random_colors()
    min_limit, max_limit = get_limit_values(random_set, random_set_10_or_11)
    # print(
    #     f"Random: {random_set}, {random_set_10_or_11}, {random_list} -- {min_limit}, {max_limit}",
    #     end=" ",
    # )

    random_b = random_list[0]
    random_g = random_list[1]
    random_r = random_list[2]

    b = np.clip(b + random_b, min_limit, max_limit).astype(np.uint8)  # type: ignore
    g = np.clip(g + random_g, min_limit, max_limit).astype(np.uint8)  # type: ignore
    r = np.clip(r + random_r, min_limit, max_limit).astype(np.uint8)  # type: ignore
    shifted_image = cv2.merge([b, g, r])

    return shifted_image


if __name__ == "__main__":
    image_name = "test__49dda928-07dd-11ef-9e27-ec8eb513014d.jpg"
    image_path = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\test\\images\\{ image_name }"

    shifted_image = random_color_shift(image_path)

    cv2.imshow("Shifted Image", shifted_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
