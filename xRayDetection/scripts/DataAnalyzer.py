import os
import pandas as pd
import random
from datetime import datetime
import argparse

"""
    每一列按照如下格式
    timestamp               confidence      label       filepath
    2023-09-01 06:52:19,    0.22,           label3,     file2.txt
    2023-09-09 15:19:36,    0.03,           label2,     file4.txt
"""


"""
    读取CSV, 返回对应的dataFrame
"""
def ReadCSV(csv_file):
    try:
        df = pd.read_csv(csv_file)
        return df
    except FileNotFoundError:
        print(f"File '{csv_file}' not found.")
        return None
    except Exception as e:
        print(f"An error occurred while reading the CSV file: {e}")
        return None

"""
    获取指定时间范围内每一种标签的的统计数量
"""
def GetStatistics(df, start_time, end_time):
    try:
        # 将时间戳列转换为日期时间类型
        df['timestamp'] = pd.to_datetime(df['timestamp'])

        # 根据时间范围筛选数据
        mask = (df['timestamp'] >= start_time) & (df['timestamp'] <= end_time)
        filtered_df = df[mask]

        # 按标签分组并计算数量，然后将结果转换为字典
        label_counts = filtered_df['label'].value_counts().to_dict()

        return label_counts
    except Exception as e:
        print(f"An error occurred while calculating label counts: {e}")
        return None

def CountLabels(csvFile: str, start_time: str, end_time: str):
    data_frame = ReadCSV(csvFile)
    return GetStatistics(data_frame, start_time, end_time)


def AppendDataToCSV(data_row: dict, csv_file: str):
    try:
        # Create a DataFrame from the new data
        new_data = pd.DataFrame([data_row])

        # Read the existing CSV file if it exists
        if pd.io.common.file_exists(csv_file):
            existing_data = pd.read_csv(csv_file)
            # Concatenate the existing data and new data
            df = pd.concat([existing_data, new_data], ignore_index=True)
        else:
            df = new_data  # If the file doesn't exist, use just the new data

        # Write the combined DataFrame to the CSV file
        df.to_csv(csv_file, index=False)

        print("Data appended to CSV file successfully.")
    except Exception as e:
        print(f"An error occurred while appending data to CSV file: {e}")

def AppendData(csvFile: str, timestamp: str, confidence: float, label:str, filepath: str):
    new_data = {
        'timestamp': timestamp,
        'confidence': confidence,
        'label': label,
        'filepath': filepath
    }

    AppendDataToCSV(new_data, csvFile)

"""
    创建测试随机数据
"""
def CreateCSVData(fileName):
    # 生成随机数据
    data = []
    for _ in range(10):
        timestamp = datetime(2023, 9, random.randint(1, 30), random.randint(0, 23), random.randint(0, 59), random.randint(0, 59))
        confidence = round(random.uniform(0, 1), 2)
        label = f"label{random.randint(1, 3)}"
        filepath = f"file{random.randint(1, 5)}.txt"
        data.append([timestamp, confidence, label, filepath])

    # 创建DataFrame
    df = pd.DataFrame(data, columns=["timestamp", "confidence", "label", "filepath"])

    # 写入CSV文件
    csv_file = fileName
    df.to_csv(csv_file, index=False)

    print(f"Random data written to '{csv_file}' successfully.")


def main(args):
    csv_file = args.csv_file
    if(not os.path.exists(csv_file)):
        print("csv file path error, not found the path:", csv_file)
        return
    

    if args.mode == 'append':
        timestamp = args.timestamp
        confidence = args.conf
        label = args.label
        filepath = args.filepath
        AppendData(csv_file, timestamp, confidence, label, filepath)

    elif args.mode == 'count':
        startTime = args.startTime
        endTime = args.endTime
        cntDict = CountLabels(csv_file, startTime, endTime)
        print(cntDict)


def ParseOpt():
    parser = argparse.ArgumentParser()
    
    parser.add_argument('--csv_file', type=str, required=True, help='Path to csv file')
    # append 则是直接增加到这个csv文件中， count则是统计所有种类标签的数量
    parser.add_argument('--mode', type=str, default='append', help='[append | count] data [to|from] csv')

    parser.add_argument('--timestamp', type=str, help="timestamp is require if append mode")
    parser.add_argument('--startTime', type=str, help="")   # 统计的起始时间
    parser.add_argument('--endTime', type=str, help='')     # 统计的截至时间

    parser.add_argument('--conf', type=float, help='target confidence')
    parser.add_argument('--label', type=str, help='the target label') # 在append 的时候需要
    parser.add_argument('--filepath', type=str, help='point to the target')

    return parser.parse_args()

if __name__ == "__main__":
    
    
    #print()

    # count test
    #python DataAnalyzer.py --csv_file=./xRayData.csv --startTime=2023-09-01 --endTime=2023-09-30 --mode=count

    # append test(这个输入时间的必须符合"%Y-%m-%d %H:%M:%S" 格式)
    # python DataAnalyzer.py --csv_file=xRayData.csv --timestamp="2023-09-11 14:30:00" --mode=append --conf=0.96 --label=Gun --filepath=p976.jpg

    opt = ParseOpt()
    main(opt)


    